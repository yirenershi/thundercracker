/* -*- mode: C; c-basic-offset: 4; intent-tabs-mode: nil -*-
 *
 * STIR -- Sifteo Tiled Image Reducer
 * Micah Elizabeth Scott <micah@misc.name>
 *
 * Copyright <c> 2011 Sifteo, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * Command line front-end.
 */

#include <stdio.h>
#include <string.h>

#include "tile.h"
#include "script.h"

#define STRINGIFY(_x)   #_x
#define TOSTRING(_x)    STRINGIFY(_x)


static void usage()
{
    fprintf(stderr,
            "\n"
            "usage: stir [OPTIONS] FILE.lua\n"
            "\n"
            "Sifteo Tiled Image Reducer, a compile-time game asset preparation\n"
            "tool. Reads a configuration file which describes your game's assets,\n"
            "compresses and reformats them, and produces code that is incorporated\n"
            "into your game's build.\n"
            "\n"
            "Options:\n"
            "  -h            Show this help message, and exit\n"
            "  -v            Verbose mode, show progress as we work\n"
            "  -o FILE.cpp   Generate a C++ source file with your asset data\n"
            "  -o FILE.h     Generate a C++ header with metadata for your assets\n"
            "  -o FILE.html  Generate a proofing sheet for your assets, in HTML format\n"
            "  VAR=VALUE     Define a script variable, prior to parsing the script\n"
            "\n"
            "Sifteo SDK (" TOSTRING(SDK_VERSION) ")\n"
            "Copyright <c> 2011-2012 Sifteo, Inc. All rights reserved.\n"
            "\n");
}

int main(int argc, char **argv)
{
    Stir::ConsoleLogger log;
    Stir::Script script(log);
    const char *scriptFile = NULL;

    /*
     * Parse command line options
    */

    for (int c = 1; c < argc; c++) {
        char *arg = argv[c];

        if (!strcmp(arg, "-h")) {
            usage();
            return 0;
        }

        if (!strcmp(arg, "-v")) {
            log.setVerbose();
            continue;
        }
         
        if (!strcmp(arg, "-o") && argv[c+1]) {
            if (script.addOutput(argv[c+1])) {
                c++;
                continue;
            } else {
                log.error("Unrecognized or duplicate output file: '%s'", argv[c+1]);
                return 1;
            }
        }

        if (arg[0] == '-') {
            log.error("Unrecognized option: '%s'", arg);
            return 1;
        }

        if (strchr(arg, '=')) {
            char *value = strchr(arg, '=') + 1;
            value[-1] = '\0';
            script.setVariable(arg, value);
            continue;
        }

        if (scriptFile) {
            log.error("Too many command line arguments");
            return 1;
        }

        scriptFile = arg;
    }

    if (!scriptFile) {
        usage();
        return 1;
    }

    /*
     * Run the script!
     */

    Stir::CIELab::initialize();

    if (!script.run(scriptFile))
        return 1;

    return 0;
}
