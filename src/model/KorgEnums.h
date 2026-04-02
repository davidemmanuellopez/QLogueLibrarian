#ifndef KORGENUMS_H
#define KORGENUMS_H

#include <QString>

namespace qlogue {

/// Unit file filter for QFileDialog
inline QString unitFileFilter() {
    return QStringLiteral(
        "All logue units (*.prlgunit *.mnlgxdunit *.ntkdigunit "
        "*.nts1mkiiunit *.nts3unit *.drmlgunit *.mk2unit);;"
        "prologue (*.prlgunit);;"
        "minilogue xd (*.mnlgxdunit);;"
        "NTS-1 (*.ntkdigunit);;"
        "NTS-1 mkII (*.nts1mkiiunit);;"
        "NTS-3 (*.nts3unit);;"
        "drumlogue (*.drmlgunit);;"
        "microKORG2 (*.mk2unit)");
}

} // namespace qlogue

#endif // KORGENUMS_H
