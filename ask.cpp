/*
    Name:	Jared S Messer
    Class:	CpS310 - Microprocessor Architecture
    Desc:	ARM7TDMI Simulator Project
    Date:	9/16/16
*/

/* ArmSim Kernel/Shell Interface definition */
#include "askapi.h"

using namespace std;

/* Registers */
word regs[16];

/* Configuration Flags */
byteb c_flags = 0x00000000;

/* Instruction Count*/
word IC = 0;


char **ask_info(void) {
    char** strings = (char**)malloc(sizeof(char*)*4);
    strings[0] = (char*)malloc(sizeof(char)*16);
    strings[1] = (char*)malloc(sizeof(char)*8);
    strings[2] = (char*)malloc(sizeof(char)*7);

    snprintf(strings[0], 16, "author=jmess107");
    snprintf(strings[1], 8, "api=1.0");
    snprintf(strings[2], 7, "mockup");
    strings[3] = NULL;

    return strings;
}

void ask_init(const struct ask_host_services *host) {
    memset(regs, 0, sizeof(regs));
    c_flags = 0x00000000;
    IC = 0;
    const char* init("CPU initialized");
    host->log_msg(init);
}

void ask_config_set(ask_config_t flags) {
    switch (flags) {
    case ac_nothing:
        c_flags = 0x00000000;
        break;
    case ac_trace_log:
        c_flags = 0x00000001;
        break;
    case ac_mpu_on:
        c_flags = 0x00000002;
        break;
    case ac_cache_on:
        c_flags = 0x00000004;
        break;
    default:
        cerr << "Unable to set config flags, setting to 0x00000000" << endl;
        c_flags = 0x00000000;
        break;
    }
}

ask_config_t ask_config_get(void) {
    switch (c_flags) {
    case 0:
        return ac_nothing;
    case 1:
        return ac_trace_log;
    case 2:
        return ac_mpu_on;
    case 4:
        return ac_cache_on;
    default:
        cerr << "Config flags not set correctly, setting to 0" << endl;
        c_flags = 0x00000000;
        return ac_nothing;
    }
}

void ask_stats_report(struct ask_stats *stats) {
    stats->instructions = IC;
    //TODO: populate rest of struct
}

word ask_reg_get(ask_mode_t bank, int index) {
    return (std::abs(index) < 16) ? regs[index] : 0xFFFFFFFF;	// If index is out of range, return some junk value: 0xFFFFFFFF
}

void ask_reg_set(ask_mode_t bank, int index, word value) {
    if (!abs(index) > 16) { cerr << "Index out of range." << endl; return; }
    regs[index] = value;
}

word ask_cpsr_get(void) {
    // TODO
    return 0;
}

void ask_cpsr_set(word value) {
    // TODO
}

int	ask_cpu_running(void) {
    // TODO
    return 0;
}

void ask_cpu_signal(ask_signal_t signal) {
    // TODO
}

int	ask_cpu_run(int cycles) {
    IC += cycles;
    return 0;
}

