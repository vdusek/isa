// VUT FIT 3BIT
// ISA 2018/2019
// Project: Programovani sitove sluzby
// Variant: 2 - Export DNS informaci pomoci protokolu Syslog
// Author: Vladimir Dusek, xdusek27
// Date: 30/9/2018
// File: main.cpp

#include <unistd.h>
#include "utils.h"
#include "arg_parser.h"
#include "pcap_parser.h"
#include "syslog.h"

using namespace std;

// Global instance of Syslog because of signal_handler
Syslog syslog;

// Global instance of ArgParser because of signal_handler
ArgParser arg_parser;

void send_to_syslog()
{
    try {
        syslog.connect();
        for (pair<string, int> elem: result_map) {
            syslog.send_log(elem.first + to_string(elem.second));
        }
        syslog.disconnect();
    }
    catch (SyslogException &exc) {
        cerr << PROJ_NAME << ": " << string(exc.what()) << flush;
        exit(RET_SYSLOG_ERR);
    }
    catch (SystemException &exc) {
        cerr << PROJ_NAME << ": " << string(exc.what()) << flush;
        exit(RET_SYS_ERR);
    }
}

void signal_handler(int signal)
{
    switch (signal) {
        case SIGALRM:
            alarm(arg_parser.get_timeout());
            send_to_syslog();
            break;

        case SIGUSR1:
            for (pair<string, int> elem: result_map) {
                cout << elem.first << elem.second << endl;
            }
            break;

        case SIGINT:
            pcap_breakloop(handle);
            exit(0);

        default:
            break;
    }
}

int main(int argc, char **argv)
{
    // Parse command line arguments
    arg_parser.set_args(argc, argv);
    try {
        arg_parser.parse();
    }
    catch (ArgumentException &exc) {
        cerr << PROJ_NAME << ": " << string(exc.what()) << flush;
        return RET_ARGS_ERR;
    }
    catch (HelpException &exc) {
        cout << HELP_TEXT << flush;
        return EXIT_SUCCESS;
    }
    syslog.set_server_address(arg_parser.get_server());

    arg_parser.debug_print(); // debug

    // Set signals handler
    if ((signal(SIGINT,  signal_handler) == SIG_ERR) ||
        (signal(SIGUSR1, signal_handler) == SIG_ERR) ||
        (signal(SIGALRM, signal_handler) == SIG_ERR))
    {
        cerr << PROJ_NAME << ": Unable to set signal handler\n" << flush;
        return RET_SYS_ERR;
    }

    // Parse pcap file or sniff on network interface
    PcapParser pcap_parser(FILTER_EXP);
    try {
        if (!arg_parser.get_resource().empty()) {
            pcap_parser.set_resource(arg_parser.get_resource());
            pcap_parser.parse_resource();
        }
        else if (!arg_parser.get_interface().empty()) {
            // Set alarm
            alarm(arg_parser.get_timeout());
            pcap_parser.set_interface(arg_parser.get_interface());
            pcap_parser.sniff_interface();
        }
    }
    catch (PcapException &exc) {
        cerr << PROJ_NAME << ": " << string(exc.what()) << flush;
        return RET_PCAP_ERR;
    }
    catch (SystemException &exc) {
        cerr << PROJ_NAME << ": " << string(exc.what()) << flush;
        return RET_SYS_ERR;
    }

    if (!arg_parser.get_resource().empty()) {
        send_to_syslog();
    }

    return EXIT_SUCCESS;
}

