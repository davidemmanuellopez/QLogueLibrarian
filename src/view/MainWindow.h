#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller/LogueCLIWrapper.h"

class QComboBox;
class QPlainTextEdit;
class QLabel;
class QPushButton;
class QLineEdit;
class QSpinBox;

namespace qlogue {

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onProbe();
    void onProbeResult(QVector<qlogue::MidiPort> ports);
    void onBrowseUnit();
    void onLoad();
    void onLoadResult(qlogue::LoadResult result);
    void onError(QString msg);

private:
    LogueCLIWrapper *m_cli;

    // toolbar / path
    QLineEdit *m_cliPathEdit;

    // probe section
    QComboBox *m_inPortCombo;
    QComboBox *m_outPortCombo;

    // load section
    QLineEdit   *m_unitPathEdit;
    QSpinBox    *m_slotSpin;      // -1 = auto (value 0), 1..N = explicit slot
    QPushButton *m_loadBtn;

    // log
    QPlainTextEdit *m_log;
    QLabel         *m_statusLabel;

    QVector<MidiPort> m_ports;

    void appendLog(const QString &text);
};

} // namespace qlogue

#endif // MAINWINDOW_H
