#include "MainWindow.h"
#include "model/KorgEnums.h"

#include <QComboBox>
#include <QFileDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSettings>
#include <QSpinBox>
#include <QStatusBar>
#include <QVBoxLayout>

namespace qlogue {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_cli(new LogueCLIWrapper(this))
{
    setWindowTitle(QStringLiteral("QLogueLibrarian"));
    resize(720, 480);

    auto *central = new QWidget;
    auto *root    = new QVBoxLayout(central);

    // ── logue-cli path ──────────────────────────────────────────────────
    {
        auto *row = new QHBoxLayout;
        row->addWidget(new QLabel(tr("logue-cli:")));
        m_cliPathEdit = new QLineEdit;
        m_cliPathEdit->setText(
            QSettings().value(QStringLiteral("tools/logueCli"),
                              QStringLiteral("logue-cli")).toString());
        connect(m_cliPathEdit, &QLineEdit::textChanged, this, [](const QString &text){
            QSettings().setValue(QStringLiteral("tools/logueCli"), text);
        });
        row->addWidget(m_cliPathEdit, 1);
        auto *browseBtn = new QPushButton(tr("..."));
        connect(browseBtn, &QPushButton::clicked, this, [this]{
            auto p = QFileDialog::getOpenFileName(this, tr("Select logue-cli"));
            if (!p.isEmpty()) m_cliPathEdit->setText(p);
        });
        row->addWidget(browseBtn);
        root->addLayout(row);
    }

    // ── Probe section ───────────────────────────────────────────────────
    {
        auto *grp = new QGroupBox(tr("MIDI Ports"));
        auto *lay = new QVBoxLayout(grp);

        auto *probeBtn = new QPushButton(tr("Probe"));
        connect(probeBtn, &QPushButton::clicked, this, &MainWindow::onProbe);
        lay->addWidget(probeBtn);

        auto *row = new QHBoxLayout;
        row->addWidget(new QLabel(tr("In:")));
        m_inPortCombo = new QComboBox;
        row->addWidget(m_inPortCombo, 1);
        row->addWidget(new QLabel(tr("Out:")));
        m_outPortCombo = new QComboBox;
        row->addWidget(m_outPortCombo, 1);
        lay->addLayout(row);

        root->addWidget(grp);
    }

    // ── Load section ────────────────────────────────────────────────────
    {
        auto *grp = new QGroupBox(tr("Load Unit"));
        auto *lay = new QHBoxLayout(grp);

        m_unitPathEdit = new QLineEdit;
        m_unitPathEdit->setPlaceholderText(tr("Select a .xxxunit file…"));
        lay->addWidget(m_unitPathEdit, 1);

        auto *browseBtn = new QPushButton(tr("Browse…"));
        connect(browseBtn, &QPushButton::clicked, this, &MainWindow::onBrowseUnit);
        lay->addWidget(browseBtn);

        lay->addWidget(new QLabel(tr("Slot:")));
        m_slotSpin = new QSpinBox;
        m_slotSpin->setMinimum(0);
        m_slotSpin->setMaximum(16);
        m_slotSpin->setValue(0);
        m_slotSpin->setSpecialValueText(tr("Auto"));  // 0 → auto (no -s flag)
        m_slotSpin->setToolTip(tr("0 = first available slot (auto)"));
        lay->addWidget(m_slotSpin);

        m_loadBtn = new QPushButton(tr("Upload"));
        m_loadBtn->setEnabled(false);
        connect(m_loadBtn, &QPushButton::clicked, this, &MainWindow::onLoad);
        lay->addWidget(m_loadBtn);

        root->addWidget(grp);
    }

    // ── Log ─────────────────────────────────────────────────────────────
    m_log = new QPlainTextEdit;
    m_log->setReadOnly(true);
    m_log->setMaximumBlockCount(500);
    root->addWidget(m_log, 1);

    // ── Status bar ──────────────────────────────────────────────────────
    m_statusLabel = new QLabel;
    statusBar()->addWidget(m_statusLabel, 1);

    setCentralWidget(central);

    // ── Signals ─────────────────────────────────────────────────────────
    connect(m_cli, &LogueCLIWrapper::probeFinished,  this, &MainWindow::onProbeResult);
    connect(m_cli, &LogueCLIWrapper::loadFinished,   this, &MainWindow::onLoadResult);
    connect(m_cli, &LogueCLIWrapper::errorOccurred,  this, &MainWindow::onError);
}

// ─── Slots ──────────────────────────────────────────────────────────────────

void MainWindow::onProbe() {
    m_cli->setCliPath(m_cliPathEdit->text());
    m_inPortCombo->clear();
    m_outPortCombo->clear();
    m_loadBtn->setEnabled(false);
    m_statusLabel->setText(tr("Probing…"));
    m_cli->probe();
}

void MainWindow::onProbeResult(QVector<MidiPort> ports) {
    m_ports = ports;
    for (auto &p : ports) {
        auto label = QStringLiteral("%1: %2").arg(p.index).arg(p.name);
        if (p.direction == MidiPort::In)
            m_inPortCombo->addItem(label, p.index);
        else
            m_outPortCombo->addItem(label, p.index);
    }
    // Auto-select ports whose name contains "SOUND"
    for (int i = 0; i < m_inPortCombo->count(); ++i) {
        if (m_inPortCombo->itemText(i).contains(QLatin1String("SOUND"), Qt::CaseInsensitive)) {
            m_inPortCombo->setCurrentIndex(i);
            break;
        }
    }
    for (int i = 0; i < m_outPortCombo->count(); ++i) {
        if (m_outPortCombo->itemText(i).contains(QLatin1String("SOUND"), Qt::CaseInsensitive)) {
            m_outPortCombo->setCurrentIndex(i);
            break;
        }
    }
    m_loadBtn->setEnabled(m_inPortCombo->count() > 0
                          && m_outPortCombo->count() > 0);
    m_statusLabel->setText(tr("Found %1 port(s)").arg(ports.size()));
    appendLog(tr("── Probe: %1 port(s) detected ──").arg(ports.size()));
}

void MainWindow::onBrowseUnit() {
    auto path = QFileDialog::getOpenFileName(
        this, tr("Select unit file"), {}, unitFileFilter());
    if (!path.isEmpty())
        m_unitPathEdit->setText(path);
}

void MainWindow::onLoad() {
    auto unit = m_unitPathEdit->text();
    if (unit.isEmpty()) return;

    int in   = m_inPortCombo->currentData().toInt();
    int out  = m_outPortCombo->currentData().toInt();
    // spinbox value 0 means "auto" → pass -1 so LogueCLIWrapper omits -s
    int slot = (m_slotSpin->value() > 0) ? m_slotSpin->value() : -1;

    m_cli->setCliPath(m_cliPathEdit->text());
    m_statusLabel->setText(tr("Uploading…"));
    m_loadBtn->setEnabled(false);
    m_cli->loadUnit(unit, in, out, slot);
}

void MainWindow::onLoadResult(LoadResult r) {
    appendLog(r.rawOutput);
    if (r.success) {
        m_statusLabel->setText(
            tr("✔ Loaded on %1 – %2").arg(r.platform, r.module));
    } else {
        m_statusLabel->setText(tr("✘ Upload failed"));
    }
    m_loadBtn->setEnabled(true);
}

void MainWindow::onError(QString msg) {
    appendLog(QStringLiteral("ERROR: ") + msg);
    m_statusLabel->setText(tr("Error"));
    m_loadBtn->setEnabled(true);
}

void MainWindow::appendLog(const QString &text) {
    m_log->appendPlainText(text);
}

} // namespace qlogue
