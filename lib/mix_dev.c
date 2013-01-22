#include <stdio.h>
#include <assert.h>
#include "mix.h"
#include "mix_chars.h"
#include "mix_dev.h"

/* Device block sizes */
int _dev_blocksize[21] = { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
    100, 100, 100, 100, 100, 100, 16, 16, 24, 14, 14 };

/* Devices */
static struct {
    FILE *fp;
} _mix_devices[21];

/* Set device file pointer */
int mix_dev_set_fp(int n, FILE *fp)
{
    if (_mix_devices[n].fp != NULL)
        fclose(_mix_devices[n].fp);

    _mix_devices[n].fp = fp;
}

int mix_dev_set_pos(int n, long pos)
{
    if (n < 16 || n == 20)
        fseek(_mix_devices[n].fp, pos * _dev_blocksize[n] * MIX_WORD_STRLEN, 
            SEEK_SET);
}

int mix_dev_rel_pos(int n, long pos)
{
    if (n < 16)
        fseek(_mix_devices[n].fp, pos * _dev_blocksize[n] * MIX_WORD_STRLEN, 
            SEEK_CUR);
}

int mix_dev_read(int n, mix_addr_t addr)
{
    int i;
    char s[MIX_WORD_STRLEN];

    if (n < 16) {
        for (i = 0; i < _dev_blocksize[n]; i++) {
            fgets(s, MIX_WORD_STRLEN, _mix_devices[n].fp);
            fgetc(_mix_devices[n].fp);
            sscanf_mix_word(s, &Mem[addr]);
            assert(VALID_ADDR(addr+1));
            ++addr;
        }
    }
    else {
        switch (n) {
        case 16: case 19:
            for (i = 0; i < _dev_blocksize[n]; i++) {
                fscanf(_mix_devices[n].fp, "%5s", s);
                Mem[addr].b[0] = _mix_chars[s[0]];
                Mem[addr].b[1] = _mix_chars[s[1]];
                Mem[addr].b[2] = _mix_chars[s[2]];
                Mem[addr].b[3] = _mix_chars[s[3]];
                Mem[addr].b[4] = _mix_chars[s[4]];
                assert(VALID_ADDR(addr+1));
                ++addr;
            }
            fscanf(_mix_devices[n].fp, "\n");
            break;
        default:
            break;
        }
    }
}

int mix_dev_write(int n, mix_addr_t addr)
{
    int i;

    if (n < 16) {
        for (i = 0; i < _dev_blocksize[n]; i++) {
            fprintf(_mix_devices[n].fp, "%s\n",
                sprintf_mix_word(Mem[addr]));
            assert(VALID_ADDR(addr+1));
            ++addr;
        }
    }
    else {
        switch (n) {
        case 17: case 18: case 20:
            for (i = 0; i < _dev_blocksize[n]; i++) {
                fprintf(_mix_devices[n].fp, "%c%c%c%c%c",
                    _ascii_chars[Mem[addr].b[0]],
                    _ascii_chars[Mem[addr].b[1]],
                    _ascii_chars[Mem[addr].b[2]],
                    _ascii_chars[Mem[addr].b[3]],
                    _ascii_chars[Mem[addr].b[4]]);
                assert(VALID_ADDR(addr+1));
                ++addr;
            }
            fprintf(_mix_devices[n].fp, "\n");
            break;
        default:
            break;
        }
    }
    
    fflush(_mix_devices[n].fp);
}

