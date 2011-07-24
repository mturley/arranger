#include "lilytools.h"

#include <QString>
#include <QStringList>

/* isBlock
 *
 * input - lilypond content
 *
 * Determines if the input is a block...
 */
bool LilyTools::isBlock(const QString& input) {
    return false;
}

bool LilyTools::isNote(const QString&);

/* tokenize
 *
 * input - lilypond content
 *
 * Returns a list of the lilypond tokens in the input. Blocks are treated as a
 * single token.
 */
QStringList LilyTools::tokenize(const QString& input) {
    QStringList token_list;

    QString delimiters   = " \n\r";
    QString start_blocks = "<{";
    QString end_blocks   = ">}";

    QString token = "";
    for(int i = 0; i < input.size(); i++) {

        int delimiter_type   = delimiters.indexOf(input[i]);
        int start_block_type = start_blocks.indexOf(input[i]);
        int end_block_type   = end_blocks.indexOf(input[i]);

        // handle chords
        if(start_block_type == 0)
            do {
                token += input[i];
                i += 1;
                end_block_type = end_blocks.indexOf(input[i]);
            } while(end_block_type != 0 && i < input.size());

        // TODO: handle {}

        if(delimiter_type == -1)
            token += input[i];

        if(delimiter_type >= 0 || i == input.size() - 1) {
            if(token.size() >= 0) {
                token_list.append(token);
                token.clear();
            }
        }
    }

    return token_list;
}

QString LilyTools::format(const QString& input,int,int) {
    QStringList tokens = tokenize(input);
    return QString();
}
