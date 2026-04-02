#ifndef LOGUECLIWRAPPER_H
#define LOGUECLIWRAPPER_H

#include <QObject>
#include <QString>
#include <QVector>

namespace qlogue {

/// One MIDI port as reported by `logue-cli probe -l`
struct MidiPort {
    enum Direction { In, Out };
    Direction direction;
    int       index;
    QString   name;    // e.g. "minilogue xd:minilogue xd _ SOUND 28:1"
};

/// Result of a `logue-cli load` invocation
struct LoadResult {
    bool    success   = false;
    QString platform;           // "minilogue xd"
    QString module;             // "Oscillator"
    QString rawOutput;          // full stderr+stdout for the log view
};

/// Thin wrapper around the logue-cli binary.
/// All heavy work runs via QProcess – signals report completion.
class LogueCLIWrapper : public QObject {
    Q_OBJECT
public:
    explicit LogueCLIWrapper(QObject *parent = nullptr);

    void setCliPath(const QString &path);

    /// Run `probe -l` and parse available MIDI ports.
    void probe();

    /// Run `load -u <unitPath> -i <inPort> -o <outPort> [-s <slot>]`
    void loadUnit(const QString &unitPath, int inPort, int outPort, int slot = -1);

signals:
    void probeFinished(QVector<qlogue::MidiPort> ports);
    void loadFinished(qlogue::LoadResult result);
    void errorOccurred(QString message);

private:
    QString m_cliPath = QStringLiteral("logue-cli");

    static QVector<MidiPort> parseProbeOutput(const QString &text);
    static LoadResult        parseLoadOutput(const QString &text, int exitCode);
};

} // namespace qlogue

#endif // LOGUECLIWRAPPER_H
