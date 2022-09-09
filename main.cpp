extern "C" {
#include <xed/xed-interface.h>
#include <xed/xed-decode.h>
}

#include <cstdio>

int main() {
    xed_error_enum_t xed_error;
    xed_decoded_inst_t xedd;
#define BUFLEN  1024
    char buffer[BUFLEN];
    xed_bool_t ok;

    // example instructions
    xed_uint_t bytes = 4;
    xed_uint8_t itext[XED_MAX_INSTRUCTION_BYTES] = {0x66, 0x67, 0x00, 0x00};

    xed_tables_init();

    xed_machine_mode_enum_t mmode = XED_MACHINE_MODE_LEGACY_32;
    xed_address_width_enum_t stack_addr_width = XED_ADDRESS_WIDTH_32b;
    xed_decoded_inst_zero(&xedd);
    xed_decoded_inst_set_mode(&xedd, mmode, stack_addr_width);
    xed_error = xed_decode(&xedd, itext, bytes);
    if (xed_error == XED_ERROR_NONE) {
        xed_decoded_inst_dump(&xedd, buffer, 1024);
        printf("%s\n", buffer);
        auto length = xed_decoded_inst_get_length(&xedd);
        auto modrm = xed_decoded_inst_get_modrm(&xedd);
        auto nprefixes = xed_decoded_inst_get_nprefixes(&xedd);
        auto nseg_prefixes = xed3_operand_get_nseg_prefixes(&xedd);
        auto nprefix66 = xed3_operand_get_prefix66(&xedd);
        printf("Length=%d, Modrm=%02X nprefixes=%d nprefix66=%d\n", length, modrm, nprefixes, nprefix66);

        ok = xed_format_context(XED_SYNTAX_XED, &xedd, buffer, BUFLEN, 0, 0, 0);
        if (ok) {
            printf("%s\n", buffer);
            return 0;
        }
        printf("Error disassembling\n");
        return 1;
    }
    printf("Decoding error\n");
    return 0;
}
