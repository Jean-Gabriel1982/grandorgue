/*
 * OurOrgan - free pipe organ simulator based on MyOrgan
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#define GIF_GAUGE_LEN 552
#define GIF_HELP_LEN 238
#define GIF_OPEN_LEN 399
#define GIF_PANIC_LEN 380
#define GIF_PROPERTY_LEN 374
#define GIF_RECORD_LEN 399
#define GIF_RELOAD_LEN 377
#define GIF_SAVE_LEN 403
#define GIF_SET_LEN 378
#define GIF_SETTINGS_LEN 380
static unsigned char GIF_ToolbarIcons[] = {
0x47,0x49,0x46,0x38,0x39,0x61,0x49,0x00,0x16,0x00,0xD5,0x00,0x00,0xFF,0xF2,0x00,
0x68,0xFF,0x00,0x8A,0xFF,0x00,0xFF,0xB9,0x00,0xBF,0xFF,0x00,0xA9,0xFF,0x00,0xFF,
0x50,0x00,0x7C,0xFF,0x00,0xB8,0xFF,0x00,0xCD,0xFF,0x00,0xE6,0xFF,0x00,0x31,0xFF,
0x00,0xE0,0xFF,0x00,0xD4,0xFF,0x00,0xDA,0xFF,0x00,0xFC,0xF8,0x00,0x92,0xFF,0x00,
0xF0,0xFF,0x00,0xFF,0xE3,0x00,0xA2,0xFF,0x00,0xB1,0xFF,0x00,0xFF,0x87,0x00,0x42,
0xFF,0x00,0x22,0xFF,0x00,0xF9,0xFB,0x00,0xC6,0xFF,0x00,0xFF,0xCF,0x00,0xF5,0xFD,
0x00,0xFF,0xD0,0x00,0xEC,0xFF,0x00,0xEB,0xFF,0x00,0xC7,0xFF,0x00,0xFF,0xA0,0x00,
0x99,0xFF,0x00,0xFF,0xA1,0x00,0x55,0xFF,0x00,0x54,0xFF,0x00,0x9A,0xFF,0x00,0x23,
0xFF,0x00,0x91,0xFF,0x00,0xFF,0x86,0x00,0x43,0xFF,0x00,0xA1,0xFF,0x00,0xF9,0xFA,
0x00,0xB0,0xFF,0x00,0xF4,0xFE,0x00,0xFD,0xF8,0x00,0xFF,0xE2,0x00,0xF1,0xFF,0x00,
0xF4,0xFD,0x00,0xFF,0x0C,0x00,0xFF,0xFF,0xFF,0x80,0x80,0x80,0x02,0x02,0x02,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0xF9,0x04,
0x00,0x00,0x00,0x00,0x00,0x2C,0x00,0x00,0x00,0x00,0x49,0x00,0x16,0x00,0x00,0x06,
0xFF,0x40,0x9A,0x70,0x48,0x2C,0x1A,0x8F,0xC8,0xA4,0x72,0x89,0xAC,0x39,0x9F,0xD0,
0xA8,0x74,0x4A,0xAD,0x5A,0xAF,0xD1,0x19,0xAD,0xB6,0xED,0x72,0xBF,0xDE,0x30,0x78,
0x2C,0x2E,0x93,0xCF,0xE6,0x2E,0xB1,0xA6,0xC5,0xBA,0xDF,0xF0,0x6B,0x91,0x9D,0x46,
0xDB,0xEB,0xF8,0xFB,0x7D,0xDD,0x8E,0xFB,0xFF,0x6E,0x73,0x6D,0x79,0x84,0x7A,0x85,
0x87,0x7C,0x5B,0x80,0x8B,0x8C,0x50,0x82,0x87,0x86,0x91,0x90,0x78,0x89,0x8D,0x96,
0x97,0x4E,0x33,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,0xA0,0xA1,0xA2,0xA3,0xA0,0x4C,0xA6,
0xA7,0xA8,0xA9,0x6B,0x98,0xAC,0x80,0x6D,0x17,0x35,0x0B,0x35,0x16,0x35,0x24,0x35,
0x01,0x35,0x07,0x35,0x02,0x35,0x27,0x35,0x21,0x35,0x13,0x35,0x05,0x35,0x2C,0x35,
0x08,0x35,0x04,0x35,0x1F,0x35,0x09,0x35,0x0D,0x35,0x0E,0x35,0x0C,0x35,0x0A,0x35,
0x1E,0x35,0x30,0x35,0x31,0x35,0x2B,0x35,0x0F,0x35,0x00,0x35,0x2F,0x35,0x1A,0x35,
0x03,0x35,0x22,0x35,0x15,0x35,0x06,0x35,0x32,0xF0,0xF0,0x74,0xAD,0xF4,0x56,0xF1,
0xF2,0xAF,0xB1,0xB3,0x35,0x23,0xB7,0xB9,0xBB,0x35,0x20,0xD4,0x28,0x11,0x6C,0x58,
0x0D,0x0A,0xC7,0x92,0x2D,0x6B,0xF6,0x2C,0xDA,0xB4,0x6A,0x35,0x3A,0xD4,0x88,0x50,
0x63,0x43,0x0D,0x0C,0xDF,0xC2,0xD5,0x90,0x50,0x83,0xC3,0xB9,0x1A,0x20,0xD6,0xB5,
0x7B,0x77,0x6F,0x5E,0xBD,0x93,0x51,0xEE,0xC9,0x98,0x07,0x4B,0x56,0x0A,0x7E,0xFE,
0x74,0xF1,0x12,0x08,0x4C,0x85,0x41,0x84,0xC8,0x94,0x65,0x60,0x08,0x4D,0x1A,0x35,
0x45,0x6B,0x12,0x29,0xB6,0xB8,0x58,0xC3,0x85,0x46,0x8E,0xE6,0xD0,0xA9,0x63,0xE7,
0x4E,0xA5,0x49,0x94,0x50,0x9D,0xB6,0x31,0xA1,0x8F,0x96,0x2D,0x5C,0x32,0x03,0x0E,
0x2C,0x48,0x0C,0xA7,0xC2,0x9D,0xCE,0x7A,0x3E,0xB4,0x86,0x8D,0xA2,0x45,0x8C,0xE0,
0xC4,0x71,0xF4,0x88,0x2E,0x24,0x8A,0x91,0x52,0x15,0x41,0x9D,0x0B,0x85,0x94,0xDD,
0xBB,0x78,0xF3,0x72,0x0A,0x02,0x00,0x3B,0x47,0x49,0x46,0x38,0x39,0x61,0x10,0x00,
0x14,0x00,0xC4,0x00,0x00,0xEE,0xEE,0xAF,0xCE,0xDC,0xB9,0xEA,0xF0,0xB5,0xE7,0xEE,
0xB5,0xD8,0xE4,0xB8,0xD9,0xD9,0xAF,0xF0,0xF0,0xAF,0xE3,0xE3,0xAF,0xD4,0xE0,0xB9,
0xF6,0xF9,0xB3,0xF8,0xFA,0xB3,0xC8,0xD5,0xB7,0xF5,0xF7,0xB5,0xF5,0xF5,0xAF,0x9F,
0x9F,0x9F,0xEC,0xF2,0xB4,0xDD,0xE7,0xB7,0x51,0x83,0xCE,0xC0,0xD2,0xBC,0x6C,0x96,
0xCA,0xAA,0xAA,0xAA,0xFF,0xFF,0xB1,0x73,0x60,0x60,0xBA,0x8B,0xA7,0x19,0x23,0xD2,
0x8F,0x69,0x5F,0xE1,0x5F,0x48,0x0F,0x23,0xDF,0x32,0x56,0x81,0x6A,0xE2,0x8E,0x3E,
0x45,0x5E,0x3A,0x1F,0x2F,0x21,0xF9,0x04,0x01,0x00,0x00,0x16,0x00,0x2C,0x00,0x00,
0x00,0x00,0x10,0x00,0x14,0x00,0x00,0x05,0x6B,0xA0,0x25,0x8E,0x64,0x69,0x9E,0x68,
0x5A,0x52,0x6C,0xEB,0xB2,0x23,0x55,0x00,0x55,0x25,0x04,0x88,0x50,0x03,0x05,0x25,
0x52,0xB4,0x4A,0x60,0x42,0x9C,0x04,0x14,0x15,0x80,0xCF,0x42,0xA9,0x3D,0x88,0x81,
0xE1,0x44,0x57,0x59,0x36,0x2B,0x03,0x22,0x83,0x40,0xA4,0x5A,0x6B,0xD8,0x81,0x84,
0x48,0x40,0x56,0x7F,0x60,0x6C,0x64,0x02,0x49,0x7F,0xC1,0x09,0x02,0x21,0x01,0x6E,
0x58,0x83,0x15,0x04,0x11,0x01,0x36,0x58,0x0B,0x69,0x0B,0x0B,0x06,0x60,0x07,0x4B,
0x4C,0x2F,0x14,0x0E,0x07,0x7E,0x87,0x29,0x14,0x86,0x2A,0x24,0x30,0x92,0x31,0x95,
0x97,0x98,0x95,0x21,0x00,0x3B,0x47,0x49,0x46,0x38,0x39,0x61,0x10,0x00,0x14,0x00,
0xD5,0x00,0x00,0xFF,0xCF,0x27,0x2D,0x9C,0x1B,0xFF,0xD0,0x2C,0xFF,0xD1,0x34,0x31,
0xAA,0x1E,0xFF,0xE2,0x7E,0xFF,0xD7,0x4C,0x37,0xBC,0x20,0xFF,0xF2,0xC5,0xFF,0xDB,
0x5F,0xDA,0xA9,0x00,0xD8,0xA8,0x00,0xFF,0xE8,0x97,0xFF,0xEF,0xB7,0xE8,0xB4,0x00,
0xFF,0xEC,0xAA,0xFF,0xF9,0xE3,0xFF,0xF6,0xD3,0xC8,0x97,0x00,0xEA,0xB6,0x00,0xFF,
0xED,0xAF,0xBE,0x8F,0x00,0x28,0x8A,0x18,0xD2,0xA3,0x00,0xCA,0x9D,0x00,0xFF,0xF2,
0xC7,0xFF,0xDF,0x71,0xFF,0xD9,0x57,0xFF,0xFD,0xEF,0x2B,0x96,0x1A,0xDB,0xE5,0xC1,
0xBA,0x8C,0x00,0xFF,0xF1,0xBF,0xFF,0xE4,0x85,0xFF,0xD9,0x53,0xF2,0xBC,0x00,0xCA,
0xD9,0xA5,0xDE,0xAF,0x01,0xBC,0xA2,0x04,0xEC,0xB7,0x00,0xDB,0xE3,0xB4,0xE4,0xB1,
0x00,0xF5,0xDD,0x7A,0xFF,0xCC,0x1B,0xFE,0xC7,0x06,0xFF,0xD5,0x41,0x2F,0xA5,0x1D,
0x33,0xAF,0x1F,0xFF,0xE0,0x75,0xF8,0xF2,0xCD,0xF5,0xEA,0xAF,0xFF,0xE5,0x89,0xFF,
0xEF,0xAD,0xFF,0xF4,0xC7,0x30,0xA6,0x1D,0x53,0x8B,0x11,0xFF,0xE3,0x81,0xCE,0xA4,
0x01,0xC8,0xA8,0x03,0xFF,0xE5,0x8B,0xE0,0xAE,0x00,0xFF,0xE1,0x7B,0x25,0x80,0x16,
0x73,0x60,0x60,0x21,0xF9,0x04,0x01,0x00,0x00,0x3F,0x00,0x2C,0x00,0x00,0x00,0x00,
0x10,0x00,0x14,0x00,0x00,0x06,0xAC,0xC0,0x9F,0x70,0x48,0x2C,0x1A,0x8F,0x48,0xA2,
0x6F,0xE9,0x4B,0x0A,0x3B,0xB6,0xC3,0xE1,0xD5,0x44,0xFA,0x0E,0x81,0xE5,0x8B,0x50,
0x15,0xF2,0xBE,0xA6,0xE5,0xD0,0xC7,0x1D,0xF2,0x66,0x1C,0x88,0xC7,0xA7,0xE3,0xDD,
0x7C,0x16,0x9B,0x65,0xC9,0xC3,0x41,0x20,0x11,0x14,0x29,0x12,0x89,0xF9,0x02,0x2E,
0x59,0x3F,0x3C,0x35,0x20,0x21,0x23,0x13,0x27,0x13,0x13,0x29,0x25,0x7F,0x3E,0x39,
0x83,0x0F,0x3B,0x0A,0x2D,0x1A,0x0D,0x98,0x98,0x32,0x3E,0x2A,0x03,0x0B,0x3C,0x0C,
0x06,0x0E,0x0C,0x19,0x19,0x08,0x08,0x14,0xA9,0x02,0x0C,0x00,0x9F,0x3B,0x0E,0x1B,
0x08,0x34,0x0F,0x0F,0x0C,0xB6,0xAC,0x06,0x0B,0x0B,0x0A,0x05,0x0A,0x1A,0x93,0x3B,
0xC1,0xC2,0x03,0x02,0x0B,0x3F,0x0A,0x22,0x0A,0x30,0x3D,0xCC,0xCD,0xCC,0x02,0x2C,
0xC6,0x0A,0x03,0x0E,0x05,0xCE,0xCE,0x2B,0xD1,0xC7,0x0E,0x02,0x3D,0x09,0xDF,0xE0,
0xDF,0xDA,0x42,0x0A,0x17,0x17,0x18,0x18,0x12,0xEA,0x15,0xEC,0x1F,0x4E,0xEF,0xF0,
0xF1,0x45,0x41,0x00,0x3B,0x47,0x49,0x46,0x38,0x39,0x61,0x10,0x00,0x14,0x00,0xD5,
0x3A,0x00,0xEC,0x00,0x00,0xC5,0x00,0x00,0xDB,0xDB,0xDB,0xC3,0xC3,0x59,0xB8,0xB8,
0x34,0xD2,0xD2,0xD3,0x6C,0x6C,0x6D,0xFF,0xFF,0x9B,0xB4,0xB4,0x34,0xFF,0xFF,0x99,
0xF2,0xF2,0xF2,0xFF,0xFF,0x7A,0x5B,0x5B,0x30,0xCA,0xCA,0xC4,0x58,0x58,0x0A,0xB1,
0xB1,0x47,0xF8,0xF8,0x94,0x6F,0x6F,0x23,0x22,0x22,0x09,0xFF,0xFF,0xE2,0xFF,0xFF,
0xCB,0x4F,0x4F,0x52,0xB1,0xB1,0x13,0xF6,0xF6,0x8E,0x46,0x46,0x49,0xC7,0xC7,0xCA,
0x58,0x58,0x58,0xE9,0xE9,0x83,0xF4,0xF4,0xF8,0x44,0x44,0x45,0xAB,0xAB,0xB1,0x49,
0x49,0x08,0xDF,0xDF,0x85,0xF4,0xF4,0xE6,0x55,0x55,0x42,0xE4,0xE4,0x61,0x66,0x66,
0x6B,0x5A,0x5A,0x05,0xA4,0xA4,0xAD,0xC2,0xC2,0xC3,0x5D,0x5D,0x5D,0xA5,0xA5,0x6E,
0xBC,0xBC,0x53,0xD1,0xD1,0xD2,0xA8,0xA8,0x28,0x6E,0x6E,0x77,0xB7,0x00,0x00,0xE5,
0x00,0x00,0xF3,0x00,0x00,0xDE,0x00,0x00,0x80,0x80,0x00,0x80,0x80,0x80,0xAA,0x00,
0x00,0x9D,0x00,0x00,0x8E,0x00,0x00,0xD2,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,
0x73,0x60,0x60,0xBA,0x8B,0xA7,0x19,0x23,0xD2,0x8F,0x69,0x5F,0xE1,0x5F,0x48,0x0F,
0x23,0xDF,0x21,0xF9,0x04,0x01,0x00,0x00,0x3A,0x00,0x2C,0x00,0x00,0x00,0x00,0x10,
0x00,0x14,0x00,0x00,0x06,0x99,0x40,0x9D,0x70,0x48,0x2C,0x1A,0x8F,0xC8,0x22,0x83,
0x94,0x24,0xCA,0x5A,0x8A,0x19,0xF1,0x46,0x75,0xA6,0x4C,0x39,0xC1,0xEC,0xF5,0x12,
0x52,0xAB,0xB2,0x84,0xE1,0x94,0x83,0x01,0x00,0xC5,0x5B,0x2C,0xB6,0x00,0x55,0x0A,
0xB0,0x78,0x51,0x26,0x8B,0x71,0x1B,0xF1,0xB8,0x74,0x28,0x9B,0xA8,0x42,0x76,0x67,
0x67,0x39,0x7B,0x42,0x32,0x14,0x04,0x10,0x07,0x76,0x5C,0x1A,0x84,0x4E,0x17,0x08,
0x23,0x54,0x6B,0x31,0x28,0x8F,0x7C,0x1B,0x16,0x2E,0x01,0x5F,0x54,0x98,0x43,0x38,
0x34,0x2E,0xA4,0x0F,0x1D,0x37,0x01,0x01,0x85,0x42,0x34,0xAD,0xAD,0x03,0x18,0x2B,
0xA4,0x2E,0x44,0x35,0xAD,0x35,0x35,0x0E,0x2C,0x22,0x19,0x39,0xAE,0x42,0x36,0xB8,
0xB8,0x3A,0x38,0x25,0x11,0x1E,0x59,0xC2,0x3A,0xC1,0x35,0x36,0x36,0x42,0x38,0x1F,
0x38,0x1C,0x33,0xCE,0xCE,0xCB,0xD7,0xA1,0x12,0x7B,0xD6,0x4D,0xDE,0xDE,0x41,0x00,
0x3B,0x47,0x49,0x46,0x38,0x39,0x61,0x10,0x00,0x14,0x00,0xD5,0x00,0x00,0x0E,0x3B,
0x98,0xDE,0xEE,0xFF,0xE4,0xF1,0xFF,0xB0,0xD7,0xFE,0xEA,0xF4,0xFF,0x22,0x50,0xA9,
0x21,0x4F,0xA9,0xA6,0xD2,0xFE,0xAB,0xD4,0xFE,0x23,0x50,0xA9,0x24,0x51,0xA9,0x25,
0x51,0xA9,0x0D,0x3B,0x98,0x8A,0xC8,0xF8,0x20,0x4F,0xA9,0xCD,0xE5,0xFE,0xAC,0xD1,
0xF4,0x1F,0x4E,0xA9,0xA2,0xCF,0xFE,0x58,0xB6,0xFF,0xBF,0xE1,0xFB,0xD6,0xEC,0xFF,
0x83,0xBD,0xF5,0x68,0x8E,0xCE,0x62,0x88,0xC9,0xBF,0xDE,0xFD,0xF0,0xF7,0xFF,0x48,
0x70,0xBA,0x6B,0x90,0xCE,0x59,0x87,0xCE,0x26,0x52,0xA9,0x5F,0x8A,0xCE,0x77,0xB6,
0xF6,0x64,0x8D,0xCE,0xB2,0xD6,0xF5,0x27,0x53,0xA9,0xD2,0xE8,0xFE,0xC7,0xE2,0xFE,
0xD8,0xEB,0xFE,0xBB,0xDD,0xFE,0xB5,0xDA,0xFE,0xC1,0xDF,0xFE,0x9D,0xCD,0xFF,0x15,
0x9F,0xFF,0x73,0x60,0x60,0xBA,0x8B,0xA7,0x19,0x23,0xD2,0x8F,0x69,0x5F,0xE1,0x5F,
0x48,0x0F,0x23,0xDF,0x32,0x56,0x81,0x6A,0xE2,0x8E,0x3E,0x45,0x5E,0x3A,0x1F,0x2F,
0x33,0x3C,0xD0,0x39,0x02,0x49,0x83,0xD8,0x3B,0x99,0xDA,0x39,0x29,0xE3,0x07,0xD4,
0x2F,0x88,0x32,0x44,0x51,0x0F,0x1A,0x56,0xF5,0xD1,0x00,0x60,0xEB,0xF5,0x21,0xF9,
0x04,0x01,0x00,0x00,0x2C,0x00,0x2C,0x00,0x00,0x00,0x00,0x10,0x00,0x14,0x00,0x00,
0x06,0x93,0x40,0x96,0x70,0x48,0x2C,0x1A,0x8F,0xC8,0x24,0x51,0xC5,0x6C,0x3A,0x8D,
0xAA,0x8A,0x86,0x40,0x10,0x08,0x02,0x8D,0xCC,0xA4,0xA8,0xA2,0x02,0xAE,0x01,0x53,
0x43,0x04,0x59,0x2D,0x09,0x5F,0x40,0x60,0x24,0x86,0x58,0x40,0x66,0xA1,0x4A,0x00,
0x00,0x30,0x4C,0x24,0x12,0x65,0xC5,0x8F,0xB3,0x54,0x01,0x77,0x0C,0x24,0x0B,0x1B,
0x18,0x1C,0x17,0x29,0x7E,0x2A,0x26,0x78,0x24,0x0F,0x25,0x25,0x29,0x29,0x27,0x27,
0x8B,0x24,0x1E,0x0B,0x0B,0x0A,0x0A,0x09,0x09,0x05,0x21,0x28,0x8B,0x0F,0x90,0x92,
0x94,0x27,0x28,0x28,0x03,0x8B,0x25,0x9D,0x9F,0x05,0x06,0x06,0x0E,0x1F,0x08,0xAC,
0x93,0x95,0xA9,0x03,0x03,0x08,0x07,0x8B,0x29,0x05,0xB0,0xB2,0x0E,0x11,0x11,0x1D,
0xBD,0x43,0x2A,0xA8,0xAA,0xBB,0xBC,0x07,0x12,0x12,0x7E,0x13,0x7D,0xD3,0xD4,0x4A,
0xD6,0xD7,0xD8,0x44,0x41,0x00,0x3B,0x47,0x49,0x46,0x38,0x39,0x61,0x10,0x00,0x14,
0x00,0xD5,0x00,0x00,0xD2,0x42,0x3C,0xD9,0x47,0x3F,0xE0,0x4C,0x42,0xB9,0x26,0x25,
0xFB,0xF0,0xF0,0xE5,0xA0,0xA0,0xF3,0x81,0x76,0xB9,0x2E,0x2D,0xB9,0x20,0x1F,0xB9,
0x31,0x30,0xB9,0x2C,0x2B,0xC5,0x1B,0x17,0xB9,0x26,0x26,0xC2,0x19,0x16,0xBA,0x05,
0x03,0xDE,0x72,0x6C,0xBB,0x05,0x04,0xD6,0x37,0x30,0xCA,0x1E,0x19,0xB9,0x15,0x14,
0xC2,0x2D,0x2B,0xC7,0x2F,0x2B,0xD1,0x2B,0x25,0xE9,0x6F,0x66,0xD2,0x38,0x31,0xE4,
0x5B,0x4F,0xDC,0x3E,0x35,0xEE,0x7A,0x70,0xC2,0x15,0x12,0xC3,0x34,0x32,0xB9,0x29,
0x29,0xB9,0x08,0x07,0xB9,0x17,0x17,0xDC,0x42,0x37,0xC0,0x13,0x11,0xDC,0x62,0x5C,
0xD8,0x43,0x3A,0xEB,0x62,0x56,0xC5,0x2F,0x2B,0xBD,0x27,0x26,0xBD,0x16,0x14,0xC0,
0x18,0x16,0xCA,0x31,0x2C,0xFF,0xFF,0xFF,0xEA,0x51,0x44,0xB9,0x1A,0x1A,0xC9,0x39,
0x35,0xB9,0x13,0x12,0xB9,0x1C,0x1B,0xDF,0x3E,0x34,0xD8,0x5E,0x58,0xCD,0x34,0x2F,
0xCC,0x3F,0x3A,0xED,0x54,0x47,0xF1,0x67,0x5B,0xBE,0x35,0x34,0xC5,0x3A,0x37,0xE6,
0x4F,0x44,0xB9,0x32,0x32,0xB9,0x01,0x00,0x73,0x60,0x60,0xBA,0x8B,0xA7,0x19,0x23,
0xD2,0x8F,0x69,0x5F,0x21,0xF9,0x04,0x01,0x00,0x00,0x3C,0x00,0x2C,0x00,0x00,0x00,
0x00,0x10,0x00,0x14,0x00,0x00,0x06,0xAC,0x40,0x9E,0x70,0x48,0x2C,0x1A,0x8F,0x48,
0x5E,0xE2,0xA0,0x50,0x30,0x10,0xC8,0x84,0x47,0x96,0xB1,0xD9,0x62,0x96,0xDD,0xAE,
0xA8,0x7B,0x6C,0x4A,0xB6,0x5A,0x2D,0x17,0x89,0x70,0xB6,0xC2,0xC3,0xC3,0x60,0x1D,
0xE7,0x72,0x82,0x00,0x40,0x84,0x3E,0x18,0xD8,0x6E,0xB8,0x1C,0x50,0xD9,0x2A,0x46,
0x78,0x1A,0x12,0x10,0x10,0x0B,0x33,0x00,0x34,0x38,0x27,0x3B,0x0C,0x17,0x61,0x39,
0x12,0x05,0x04,0x04,0x05,0x0D,0x89,0x38,0x37,0x3B,0x08,0x61,0x63,0x10,0x04,0x2B,
0x2B,0x04,0x0E,0x38,0x98,0x3A,0x9A,0x9C,0x39,0x9E,0xA0,0xA2,0xA4,0x37,0xA6,0x08,
0x2C,0x63,0x02,0x0B,0x92,0x94,0x28,0xA5,0x03,0x3B,0x2D,0x21,0x7A,0x18,0x0D,0x0E,
0x0E,0x29,0x14,0xAE,0x3A,0x30,0x5B,0x3B,0x24,0x71,0x88,0x34,0x89,0xC4,0xB9,0x42,
0x3B,0x2A,0x72,0xCC,0xAD,0x3A,0x3A,0x03,0x1F,0x68,0x3C,0x3B,0x26,0x2E,0xCD,0xC4,
0x13,0x20,0xDA,0xD0,0x3B,0x1D,0x37,0xE7,0x03,0x2F,0x5A,0x48,0x5A,0xED,0xE3,0x49,
0xF0,0xF1,0x43,0x41,0x00,0x3B,0x47,0x49,0x46,0x38,0x39,0x61,0x10,0x00,0x14,0x00,
0xD5,0x00,0x00,0xDE,0xEE,0xFF,0xC1,0xDF,0xFE,0xA6,0xD2,0xFE,0xEA,0xF4,0xFF,0xBE,
0xE0,0xE3,0xB5,0xDA,0xFE,0xB3,0xDB,0xE3,0xA8,0xD7,0xE3,0xC8,0xE6,0xE3,0xAE,0xD9,
0xE3,0x8A,0xC8,0xF8,0xCD,0xE8,0xE4,0x58,0xB6,0xFF,0xAC,0xD1,0xF4,0xA4,0xD4,0xE3,
0xA2,0xCF,0xFE,0xC2,0xE3,0xE3,0xC4,0xE2,0xFF,0xBE,0xDF,0xFF,0xB3,0xD9,0xFF,0x9C,
0xD4,0xB6,0xD8,0xEB,0xFE,0x9C,0xD7,0xA3,0xD2,0xE8,0xFE,0xD6,0xEC,0xFF,0xC9,0xE4,
0xFF,0xB2,0xD6,0xF5,0x5D,0xBB,0xF1,0xA4,0xD8,0xB6,0x83,0xBD,0xF5,0xF0,0xF7,0xFF,
0xDE,0xEE,0xFC,0xA7,0xD7,0xCB,0x77,0xB6,0xF6,0x86,0xCC,0xA3,0xAB,0xDA,0xCB,0xA4,
0xDB,0xA3,0xCD,0xE5,0xFE,0x93,0xD1,0xB6,0xBB,0xDD,0xFE,0xAB,0xD4,0xFE,0xB0,0xD7,
0xFE,0xE4,0xF1,0xFF,0xC7,0xE2,0xFE,0x9D,0xCD,0xFF,0x3D,0xB9,0x00,0x15,0x9F,0xFF,
0x73,0x60,0x60,0xBA,0x8B,0xA7,0x19,0x23,0xD2,0x8F,0x69,0x5F,0xE1,0x5F,0x48,0x0F,
0x23,0xDF,0x32,0x56,0x81,0x6A,0xE2,0x8E,0x3E,0x45,0x5E,0x3A,0x1F,0x2F,0x33,0x3C,
0xD0,0x39,0x02,0x49,0x83,0xD8,0x3B,0x99,0xDA,0x39,0x29,0xE3,0x07,0xD4,0x2F,0x88,
0x32,0x44,0x51,0x21,0xF9,0x04,0x01,0x00,0x00,0x2F,0x00,0x2C,0x00,0x00,0x00,0x00,
0x10,0x00,0x14,0x00,0x00,0x06,0x96,0xC0,0x97,0x70,0x48,0x2C,0x1A,0x8F,0xC8,0x24,
0x31,0x13,0x91,0x4C,0x58,0xD0,0xA8,0x31,0x82,0xF1,0x0C,0x06,0x2A,0x15,0x40,0xF1,
0x61,0x14,0x25,0xD7,0x2C,0x00,0x50,0x51,0x68,0x1A,0x2E,0xE2,0x04,0xAB,0x5A,0x2C,
0x10,0x08,0x45,0xA3,0x13,0x4A,0x0B,0x59,0x5A,0x52,0x6B,0xDF,0xDA,0xB8,0xFE,0x76,
0x2F,0x2C,0x64,0x2D,0x16,0x10,0x04,0x1C,0x2D,0x2B,0x01,0x01,0x81,0x2C,0x08,0x7C,
0x04,0x2B,0x2B,0x20,0x06,0x27,0x27,0x8E,0x17,0x10,0x2D,0x92,0x2B,0x06,0x2D,0x09,
0x27,0x05,0x8E,0x25,0x04,0x23,0x8B,0x9F,0x7B,0x07,0x29,0x8E,0x93,0x2D,0x14,0x09,
0x09,0x26,0x2D,0x29,0x29,0x28,0xAD,0x01,0x14,0x7C,0x2D,0x22,0xB6,0x02,0x8E,0x01,
0x97,0x07,0x07,0x0E,0x0E,0x28,0x28,0x02,0xBF,0x43,0x2C,0xA2,0x05,0xB5,0xC7,0xC9,
0x0F,0x0F,0x81,0x0C,0x80,0xD6,0xD7,0x4A,0xD9,0xDA,0xDB,0x44,0x41,0x00,0x3B,0x47,
0x49,0x46,0x38,0x39,0x61,0x10,0x00,0x14,0x00,0xD5,0x3F,0x00,0x89,0x73,0xCE,0x75,
0x55,0xD4,0xC9,0xC2,0xD6,0x69,0x48,0xCC,0xA5,0x93,0xE1,0x80,0x66,0xD1,0x7B,0x5F,
0xCE,0xEF,0xEB,0xF1,0xEC,0xE8,0xF0,0x78,0x5B,0xCC,0xE3,0xDE,0xE8,0xEF,0xED,0xF2,
0xEB,0xE8,0xEF,0x50,0x33,0xAA,0x87,0x6E,0xD8,0xEC,0xE9,0xEF,0x80,0x64,0xD7,0xD3,
0xCE,0xDF,0xAC,0xA3,0xC1,0xE8,0xE4,0xEE,0x52,0x30,0xB6,0x55,0x34,0xB8,0xCE,0xC9,
0xDB,0xB0,0xA8,0xC4,0xF0,0xEE,0xF3,0x89,0x70,0xDA,0x66,0x49,0xBF,0x9D,0x8F,0xC7,
0x5B,0x34,0xC2,0xC1,0xB8,0xD7,0x60,0x43,0xBD,0xB6,0xAF,0xC9,0xAA,0x9E,0xCA,0xA6,
0x92,0xE7,0x7C,0x62,0xD0,0xE2,0xDC,0xE8,0x79,0x5C,0xD5,0xAC,0x9C,0xE0,0xA6,0x96,
0xD5,0xA4,0x90,0xDF,0x7F,0x65,0xCF,0x78,0x5A,0xCB,0xA3,0x8F,0xDE,0xB0,0xA3,0xD5,
0xB5,0xAB,0xD2,0xB7,0xA8,0xDB,0xBF,0xB2,0xE1,0x7C,0x60,0xD6,0x58,0x35,0xBF,0x59,
0x38,0xBB,0x5C,0x39,0xC3,0x8E,0x78,0xD2,0xC0,0xB7,0xCF,0xA8,0x99,0xD0,0xA3,0x95,
0xCC,0xC3,0xBC,0xD2,0xEF,0xED,0xF3,0x88,0x6E,0xD9,0xE2,0xDD,0xE8,0x88,0x6F,0xD9,
0xED,0xEA,0xF0,0x5F,0x42,0xBD,0x71,0x53,0xD3,0x73,0x60,0x60,0x21,0xF9,0x04,0x01,
0x00,0x00,0x3F,0x00,0x2C,0x00,0x00,0x00,0x00,0x10,0x00,0x14,0x00,0x00,0x06,0xB0,
0xC0,0x9F,0x70,0x48,0x2C,0x1A,0x8F,0x44,0x03,0x8A,0xC7,0x6C,0x3A,0x79,0x85,0xC2,
0xCF,0xE0,0x7B,0x10,0x76,0xD8,0xEC,0x8E,0xA0,0xC8,0x68,0xA6,0x55,0xCC,0x62,0x4C,
0xE6,0x3D,0x14,0x10,0x0F,0xD8,0xBA,0xCB,0xB9,0xDF,0x27,0x45,0xA0,0xB7,0xC6,0x1C,
0x78,0x8C,0xBC,0x5E,0xE1,0xA3,0x1B,0x06,0x6C,0x39,0x0E,0x83,0x83,0x2A,0x7C,0x7E,
0x32,0x3A,0x08,0x0F,0x38,0x8D,0x8E,0x38,0x87,0x3F,0x09,0x32,0x2D,0x23,0x3A,0x97,
0x98,0x97,0x2E,0x7D,0x92,0x30,0x14,0x32,0x03,0x24,0x19,0x10,0x01,0x3E,0xA6,0xA6,
0x74,0x29,0x14,0x1C,0x21,0x1D,0x2C,0x35,0x1F,0x12,0x20,0x15,0x15,0x31,0x9C,0x29,
0x1C,0x03,0x1D,0x05,0x33,0x36,0x12,0x17,0x02,0x7D,0x0D,0xB7,0x03,0x01,0x37,0x05,
0x00,0x1B,0xC0,0x13,0xA6,0xC3,0x74,0x3E,0x01,0x10,0x34,0x28,0xC9,0x02,0x13,0x11,
0xCD,0x9C,0x3F,0x1A,0x2F,0x1F,0x22,0x00,0x2B,0xD7,0x16,0xD9,0x74,0x42,0x1E,0x12,
0x1B,0x26,0x25,0x11,0x16,0x02,0x3D,0x3D,0x0D,0xE5,0x48,0xF3,0xF4,0xF5,0xF4,0x41,
0x00,0x3B,0x47,0x49,0x46,0x38,0x39,0x61,0x10,0x00,0x14,0x00,0xD5,0x00,0x00,0xE6,
0xE8,0xC1,0xC5,0xC4,0x94,0xC6,0xC5,0x9A,0xDD,0xDE,0xBB,0xD1,0xD3,0x9F,0xC6,0xC5,
0x99,0xC4,0xC3,0x92,0xD6,0xD8,0xA2,0xD8,0xD9,0xB1,0xC3,0xC3,0x8F,0xCB,0xCC,0x9B,
0xC4,0xC3,0x91,0xDB,0xDE,0xAA,0xC6,0xC6,0x8F,0xDE,0xE1,0xB2,0xD3,0xD5,0xA4,0xC7,
0xC6,0x97,0xD4,0xD7,0xA3,0xC3,0xC2,0x8E,0xC6,0xC5,0x98,0xDA,0xDD,0xAE,0xE1,0xE3,
0xB9,0xCB,0xCB,0x9D,0xC7,0xC7,0x8F,0xCC,0xCD,0x9C,0xCE,0xD0,0x9A,0xC2,0xC2,0x8A,
0xCB,0xCB,0x9B,0xE3,0xE5,0xBE,0xD9,0xDB,0xB3,0xCE,0xCF,0xA0,0xC6,0xC5,0x97,0xD7,
0xDA,0xA8,0xDC,0xE0,0xAC,0xCF,0xD0,0xA2,0xE1,0xE4,0xB5,0xCA,0xCA,0x9E,0xCC,0xCC,
0xA0,0xD1,0xD3,0xA4,0xD5,0xD7,0xA6,0xDA,0xDD,0xAA,0xC7,0xC6,0x9C,0xC1,0xC0,0x87,
0x66,0x65,0x47,0x73,0x60,0x60,0xBA,0x8B,0xA7,0x19,0x23,0xD2,0x8F,0x69,0x5F,0xE1,
0x5F,0x48,0x0F,0x23,0xDF,0x32,0x56,0x81,0x6A,0xE2,0x8E,0x3E,0x45,0x5E,0x3A,0x1F,
0x2F,0x33,0x3C,0xD0,0x39,0x02,0x49,0x83,0xD8,0x3B,0x99,0xDA,0x39,0x29,0xE3,0x07,
0xD4,0x2F,0x88,0x32,0x44,0x51,0x0F,0x1A,0x56,0xF5,0xD1,0x00,0x60,0xEB,0xF5,0x21,
0xF9,0x04,0x01,0x00,0x00,0x2C,0x00,0x2C,0x00,0x00,0x00,0x00,0x10,0x00,0x14,0x00,
0x00,0x06,0x97,0x40,0x96,0x70,0x48,0x2C,0x1A,0x8F,0x48,0x96,0x6A,0xB9,0x4C,0x2E,
0x25,0x1F,0x12,0xC9,0xD2,0x2C,0xAA,0x16,0x89,0x54,0x8A,0x54,0x12,0x79,0x36,0x2A,
0xA2,0x4A,0xF3,0xD1,0x72,0x45,0x22,0xD3,0x09,0x13,0x16,0xAA,0xCA,0xDB,0x6E,0xFA,
0x04,0x7A,0xB4,0x55,0x86,0x95,0xBE,0xA4,0x5F,0x9D,0xFA,0x11,0x06,0x4A,0x1F,0x2B,
0x5C,0x7C,0x6A,0x74,0x2B,0x21,0x0C,0x01,0x4A,0x29,0x7D,0x22,0x7A,0x74,0x28,0x8A,
0x23,0x8D,0x2A,0x86,0x2B,0x26,0x7E,0x20,0x28,0x94,0x23,0x15,0x1F,0x4A,0x10,0x7D,
0x9B,0x7A,0x28,0x21,0x2B,0x00,0x1D,0x05,0x6E,0x0A,0x26,0x6A,0x9D,0xA8,0x23,0x00,
0x00,0x02,0x43,0x2A,0x0D,0xB1,0x9E,0x21,0x23,0xB4,0x03,0xB7,0xB8,0x17,0x04,0x04,
0xB3,0x0E,0x1C,0x03,0x29,0x46,0x4B,0x19,0x07,0x23,0x14,0x08,0x13,0xCA,0x48,0x01,
0x1F,0x05,0x02,0xD3,0x49,0xDA,0xDB,0xDC,0xDA,0x41,0x00,0x3B,0x47,0x49,0x46,0x38,
0x39,0x61,0x10,0x00,0x14,0x00,0xD5,0x00,0x00,0xE1,0xA6,0x30,0xC3,0xDA,0xFD,0x34,
0x53,0x9F,0xAE,0xCC,0xFE,0x15,0x11,0x0B,0xD1,0x96,0x20,0xDF,0xA0,0x22,0xE7,0xF1,
0xFE,0xDE,0xEB,0xFE,0x30,0x51,0x9F,0xAC,0xCB,0xFE,0xAF,0xCD,0xFE,0xDA,0xE8,0xFE,
0xFF,0x25,0x25,0xC1,0xD9,0xFD,0x33,0x00,0x00,0xE3,0xEE,0xFE,0xC8,0x8F,0x20,0xC6,
0xDB,0xFE,0x6A,0x82,0xBC,0x35,0x53,0x9F,0xC4,0x61,0x00,0x2D,0x4E,0x9F,0x60,0x7A,
0xBA,0x32,0x51,0x9F,0xA9,0xCA,0xFE,0xDD,0xAD,0x53,0xE5,0xEF,0xFE,0x82,0x97,0xBA,
0x2D,0x4F,0x9F,0x9C,0x00,0x00,0xEB,0x1E,0x1E,0xCF,0xDE,0xF8,0x1B,0x48,0x93,0x0F,
0x2D,0x5D,0xAB,0xAC,0xB3,0x5E,0x7C,0xC0,0xA1,0x80,0x43,0xCA,0x90,0x20,0x30,0x50,
0x9F,0x20,0x54,0xAB,0x99,0xB3,0xE9,0x68,0x82,0xBC,0xA9,0x03,0x03,0xB6,0x08,0x08,
0xCF,0xE1,0xFE,0x67,0x81,0xBC,0xEA,0xF2,0xFE,0xCB,0xDB,0xF8,0xAB,0xC3,0xF2,0xDC,
0xE9,0xFE,0xE0,0xEC,0xFE,0x57,0x48,0x30,0xEC,0xB8,0x57,0x1B,0x4D,0x9F,0x1B,0x42,
0x83,0x00,0x00,0x00,0x73,0x60,0x60,0xBA,0x8B,0xA7,0x19,0x23,0xD2,0x8F,0x69,0x5F,
0xE1,0x5F,0x48,0x0F,0x23,0xDF,0x32,0x56,0x81,0x21,0xF9,0x04,0x01,0x00,0x00,0x39,
0x00,0x2C,0x00,0x00,0x00,0x00,0x10,0x00,0x14,0x00,0x00,0x06,0x99,0xC0,0x9C,0x70,
0x48,0x2C,0x1A,0x8F,0xC8,0xA4,0x32,0x47,0xA3,0x11,0x9E,0x84,0x5C,0xE3,0x48,0x2B,
0x69,0x6A,0xD8,0xDA,0x63,0x5A,0xA4,0xD5,0x70,0x80,0x70,0xB8,0xF2,0xC9,0xA1,0x6C,
0x68,0x2F,0x8E,0x83,0x2B,0xB8,0x0B,0x15,0x56,0xCE,0xF6,0x3A,0xA8,0x47,0x38,0x03,
0xCE,0x14,0x89,0x3C,0x56,0x73,0x76,0x5F,0x20,0x79,0x85,0x38,0x38,0x39,0x1E,0x81,
0x87,0x10,0x33,0x30,0x85,0x29,0x22,0x44,0x36,0x1B,0x13,0x13,0x33,0x2A,0x2E,0x17,
0x38,0x24,0x01,0x37,0x93,0x8D,0x33,0x08,0x32,0x32,0x0C,0x31,0x01,0x0E,0x9F,0x43,
0x36,0x33,0x14,0x14,0x32,0x02,0x02,0x18,0x09,0x27,0x03,0xAA,0x42,0xAC,0xA3,0xA5,
0x01,0xA8,0x03,0xB6,0x93,0x08,0xB1,0x2D,0x09,0x09,0x1D,0x16,0x16,0x0A,0xB7,0x73,
0x32,0x12,0x12,0x01,0x0B,0x0B,0x03,0x0A,0x0A,0x19,0xCA,0x21,0x37,0xD8,0xD9,0xDA,
0xCA,0x4B,0xDD,0xDE,0x4B,0x41,0x00,0x3B,
};
static unsigned char* GIF_Gauge = GIF_ToolbarIcons;
static unsigned char* GIF_Help = GIF_Gauge + GIF_GAUGE_LEN;
static unsigned char* GIF_Open = GIF_Help + GIF_HELP_LEN;
static unsigned char* GIF_Panic = GIF_Open + GIF_OPEN_LEN;
static unsigned char* GIF_Property = GIF_Panic + GIF_PANIC_LEN;
static unsigned char* GIF_Record = GIF_Property + GIF_PROPERTY_LEN;
static unsigned char* GIF_Reload = GIF_Record + GIF_RECORD_LEN;
static unsigned char* GIF_Save = GIF_Reload + GIF_RELOAD_LEN;
static unsigned char* GIF_Set = GIF_Save + GIF_SAVE_LEN;
static unsigned char* GIF_Settings = GIF_Set + GIF_SET_LEN;
