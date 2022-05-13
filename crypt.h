#ifndef _CRYPT_
#define _CRYPT_

#include "bits.h"

#define BOXSZ 256

// Call 8 times on same byte to get back to original byte value
#define permute8bits_byte0(H0) ((GETBIT0_ASBIT3((H0))   | GETBIT3_ASBIT6((H0))   | GETBIT6_ASBIT1((H0))   | GETBIT1_ASBIT4((H0))   | GETBIT4_ASBIT7((H0))   | GETBIT7_ASBIT2((H0))   | GETBIT2_ASBIT5((H0))   | GETBIT5_ASBIT0((H0)))) 	 
#define permute8bits_byte1(H0) ((GETBIT8_ASBIT11((H0))  | GETBIT11_ASBIT14((H0)) | GETBIT14_ASBIT9((H0))  | GETBIT9_ASBIT12((H0))  | GETBIT12_ASBIT15((H0)) | GETBIT15_ASBIT10((H0)) | GETBIT10_ASBIT13((H0)) | GETBIT13_ASBIT8((H0))))	 
#define permute8bits_byte2(H0) ((GETBIT16_ASBIT19((H0)) | GETBIT19_ASBIT22((H0)) | GETBIT22_ASBIT17((H0)) | GETBIT17_ASBIT20((H0)) | GETBIT20_ASBIT23((H0)) | GETBIT23_ASBIT18((H0)) | GETBIT18_ASBIT21((H0)) | GETBIT21_ASBIT16((H0)))) 
#define permute8bits_byte3(H0) ((GETBIT24_ASBIT27((H0)) | GETBIT27_ASBIT30((H0)) | GETBIT30_ASBIT25((H0)) | GETBIT25_ASBIT28((H0)) | GETBIT28_ASBIT31((H0)) | GETBIT31_ASBIT26((H0)) | GETBIT26_ASBIT29((H0)) | GETBIT29_ASBIT24((H0)))) 
#define permute8bits_byte4(H0) ((GETBIT32_ASBIT35((H0)) | GETBIT35_ASBIT38((H0)) | GETBIT38_ASBIT33((H0)) | GETBIT33_ASBIT36((H0)) | GETBIT36_ASBIT39((H0)) | GETBIT39_ASBIT34((H0)) | GETBIT34_ASBIT37((H0)) | GETBIT37_ASBIT32((H0)))) 
#define permute8bits_byte5(H0) ((GETBIT40_ASBIT43((H0)) | GETBIT43_ASBIT46((H0)) | GETBIT46_ASBIT41((H0)) | GETBIT41_ASBIT44((H0)) | GETBIT44_ASBIT47((H0)) | GETBIT47_ASBIT42((H0)) | GETBIT42_ASBIT45((H0)) | GETBIT45_ASBIT40((H0)))) 
#define permute8bits_byte6(H0) ((GETBIT48_ASBIT51((H0)) | GETBIT51_ASBIT54((H0)) | GETBIT54_ASBIT49((H0)) | GETBIT49_ASBIT52((H0)) | GETBIT52_ASBIT55((H0)) | GETBIT55_ASBIT50((H0)) | GETBIT50_ASBIT53((H0)) | GETBIT53_ASBIT48((H0)))) 
#define permute8bits_byte7(H0) ((GETBIT56_ASBIT59((H0)) | GETBIT59_ASBIT62((H0)) | GETBIT62_ASBIT57((H0)) | GETBIT57_ASBIT60((H0)) | GETBIT60_ASBIT63((H0)) | GETBIT63_ASBIT58((H0)) | GETBIT58_ASBIT61((H0)) | GETBIT61_ASBIT56((H0))))   

// Call 8 times on same byte to get back to original byte value
#define unify8bits_byte0(H0) ((GETBIT3_ASBIT0((H0))   | GETBIT6_ASBIT3((H0))   | GETBIT1_ASBIT6((H0))   | GETBIT4_ASBIT1((H0))   | GETBIT7_ASBIT4((H0))   | GETBIT2_ASBIT7((H0))   | GETBIT5_ASBIT2((H0))   | GETBIT0_ASBIT5((H0)))) 	 
#define unify8bits_byte1(H0) ((GETBIT11_ASBIT8((H0))  | GETBIT14_ASBIT11((H0)) | GETBIT9_ASBIT14((H0))  | GETBIT12_ASBIT9((H0))  | GETBIT15_ASBIT12((H0)) | GETBIT10_ASBIT15((H0)) | GETBIT13_ASBIT10((H0)) | GETBIT8_ASBIT13((H0))))	 
#define unify8bits_byte2(H0) ((GETBIT19_ASBIT16((H0)) | GETBIT22_ASBIT19((H0)) | GETBIT17_ASBIT22((H0)) | GETBIT20_ASBIT17((H0)) | GETBIT23_ASBIT20((H0)) | GETBIT18_ASBIT23((H0)) | GETBIT21_ASBIT18((H0)) | GETBIT16_ASBIT21((H0)))) 
#define unify8bits_byte3(H0) ((GETBIT27_ASBIT24((H0)) | GETBIT30_ASBIT27((H0)) | GETBIT25_ASBIT30((H0)) | GETBIT28_ASBIT25((H0)) | GETBIT31_ASBIT28((H0)) | GETBIT26_ASBIT31((H0)) | GETBIT29_ASBIT26((H0)) | GETBIT24_ASBIT29((H0)))) 
#define unify8bits_byte4(H0) ((GETBIT35_ASBIT32((H0)) | GETBIT38_ASBIT35((H0)) | GETBIT33_ASBIT38((H0)) | GETBIT36_ASBIT33((H0)) | GETBIT39_ASBIT36((H0)) | GETBIT34_ASBIT39((H0)) | GETBIT37_ASBIT34((H0)) | GETBIT32_ASBIT37((H0)))) 
#define unify8bits_byte5(H0) ((GETBIT43_ASBIT40((H0)) | GETBIT46_ASBIT43((H0)) | GETBIT41_ASBIT46((H0)) | GETBIT44_ASBIT41((H0)) | GETBIT47_ASBIT44((H0)) | GETBIT42_ASBIT47((H0)) | GETBIT45_ASBIT42((H0)) | GETBIT40_ASBIT45((H0)))) 
#define unify8bits_byte6(H0) ((GETBIT51_ASBIT48((H0)) | GETBIT54_ASBIT51((H0)) | GETBIT49_ASBIT54((H0)) | GETBIT52_ASBIT49((H0)) | GETBIT55_ASBIT52((H0)) | GETBIT50_ASBIT55((H0)) | GETBIT53_ASBIT50((H0)) | GETBIT48_ASBIT53((H0)))) 
#define unify8bits_byte7(H0) ((GETBIT59_ASBIT56((H0)) | GETBIT62_ASBIT59((H0)) | GETBIT57_ASBIT62((H0)) | GETBIT60_ASBIT57((H0)) | GETBIT63_ASBIT60((H0)) | GETBIT58_ASBIT63((H0)) | GETBIT61_ASBIT58((H0)) | GETBIT56_ASBIT61((H0)))) 


// Call 56 times on same 7-byte key to get back to original key value
#define permute7bytes(H0) ((permute8bits_byte3(GETBYTE0_ASBYTE3((H0))) | permute8bits_byte6(GETBYTE3_ASBYTE6((H0))) | permute8bits_byte2(GETBYTE6_ASBYTE2((H0))) | permute8bits_byte5(GETBYTE2_ASBYTE5((H0))) | permute8bits_byte1(GETBYTE5_ASBYTE1((H0))) | permute8bits_byte4(GETBYTE1_ASBYTE4((H0))) | permute8bits_byte0(GETBYTE4_ASBYTE0((H0)))))
#define unify7bytes(H0)   ((unify8bits_byte0(GETBYTE3_ASBYTE0((H0)))   | unify8bits_byte3(GETBYTE6_ASBYTE3((H0)))   | unify8bits_byte6(GETBYTE2_ASBYTE6((H0)))   | unify8bits_byte2(GETBYTE5_ASBYTE2((H0)))   | unify8bits_byte5(GETBYTE1_ASBYTE5((H0)))   | unify8bits_byte1(GETBYTE4_ASBYTE1((H0)))   | unify8bits_byte4(GETBYTE0_ASBYTE4((H0)))))


// SBOX FROM AES
uint8_t aes[BOXSZ] = 
// 	00 	01 	02 	03 	04 	05 	06 	07 	08 	09 	0a 	0b 	0c 	0d 	0e 	0f
/*00*/{	0x63, 	0x7c, 	0x77, 	0x7b, 	0xf2, 	0x6b, 	0x6f, 	0xc5, 	0x30, 	0x01, 	0x67, 	0x2b, 	0xfe, 	0xd7, 	0xab, 	0x76,
/*10*/ 	0xca, 	0x82, 	0xc9, 	0x7d, 	0xfa, 	0x59, 	0x47, 	0xf0, 	0xad, 	0xd4, 	0xa2, 	0xaf, 	0x9c, 	0xa4, 	0x72, 	0xc0,
/*20*/  0xb7, 	0xfd, 	0x93, 	0x26, 	0x36, 	0x3f, 	0xf7, 	0xcc, 	0x34, 	0xa5, 	0xe5, 	0xf1, 	0x71, 	0xd8, 	0x31, 	0x15,
/*30*/ 	0x04, 	0xc7, 	0x23, 	0xc3, 	0x18, 	0x96, 	0x05, 	0x9a, 	0x07, 	0x12, 	0x80, 	0xe2, 	0xeb, 	0x27, 	0xb2, 	0x75,
/*40*/ 	0x09,	0x83, 	0x2c, 	0x1a, 	0x1b, 	0x6e, 	0x5a, 	0xa0, 	0x52, 	0x3b, 	0xd6, 	0xb3, 	0x29, 	0xe3, 	0x2f, 	0x84,
/*50*/ 	0x53, 	0xd1, 	0x00, 	0xed, 	0x20, 	0xfc, 	0xb1, 	0x5b, 	0x6a, 	0xcb, 	0xbe, 	0x39, 	0x4a, 	0x4c, 	0x58, 	0xcf,
/*60*/ 	0xd0, 	0xef, 	0xaa, 	0xfb, 	0x43, 	0x4d, 	0x33, 	0x85, 	0x45, 	0xf9, 	0x02, 	0x7f, 	0x50, 	0x3c, 	0x9f, 	0xa8,
/*70*/ 	0x51, 	0xa3, 	0x40, 	0x8f, 	0x92, 	0x9d, 	0x38, 	0xf5, 	0xbc, 	0xb6, 	0xda, 	0x21, 	0x10, 	0xff, 	0xf3, 	0xd2,
/*80*/ 	0xcd, 	0x0c, 	0x13, 	0xec, 	0x5f, 	0x97, 	0x44, 	0x17, 	0xc4, 	0xa7, 	0x7e, 	0x3d, 	0x64, 	0x5d, 	0x19, 	0x73,
/*90*/ 	0x60, 	0x81, 	0x4f, 	0xdc, 	0x22, 	0x2a, 	0x90, 	0x88, 	0x46, 	0xee, 	0xb8, 	0x14, 	0xde, 	0x5e, 	0x0b, 	0xdb,
/*a0*/ 	0xe0, 	0x32, 	0x3a, 	0x0a, 	0x49, 	0x06, 	0x24, 	0x5c, 	0xc2, 	0xd3, 	0xac, 	0x62, 	0x91, 	0x95, 	0xe4, 	0x79,
/*b0*/ 	0xe7, 	0xc8, 	0x37, 	0x6d, 	0x8d, 	0xd5, 	0x4e, 	0xa9, 	0x6c, 	0x56, 	0xf4, 	0xea, 	0x65, 	0x7a, 	0xae, 	0x08,
/*c0*/ 	0xba, 	0x78, 	0x25, 	0x2e, 	0x1c, 	0xa6, 	0xb4, 	0xc6, 	0xe8, 	0xdd, 	0x74, 	0x1f, 	0x4b, 	0xbd, 	0x8b, 	0x8a,
/*d0*/ 	0x70, 	0x3e, 	0xb5, 	0x66, 	0x48, 	0x03, 	0xf6, 	0x0e, 	0x61, 	0x35, 	0x57, 	0xb9, 	0x86, 	0xc1, 	0x1d, 	0x9e,
/*e0*/ 	0xe1, 	0xf8, 	0x98, 	0x11, 	0x69, 	0xd9, 	0x8e, 	0x94, 	0x9b, 	0x1e, 	0x87, 	0xe9, 	0xce, 	0x55, 	0x28, 	0xdf,
/*f0*/ 	0x8c, 	0xa1, 	0x89, 	0x0d, 	0xbf, 	0xe6, 	0x42, 	0x68, 	0x41, 	0x99, 	0x2d, 	0x0f, 	0xb0, 	0x54, 	0xbb, 	0x16 }; 

// INVERSE SBOX FROM AES
uint8_t aesinv[BOXSZ] =
// 	00 	01 	02 	03 	04 	05 	06 	07 	08 	09 	0a 	0b 	0c 	0d 	0e 	0f
/*00*/{ 0x52, 	0x09, 	0x6a, 	0xd5, 	0x30, 	0x36, 	0xa5, 	0x38, 	0xbf, 	0x40, 	0xa3, 	0x9e, 	0x81, 	0xf3, 	0xd7, 	0xfb,
/*10*/ 	0x7c, 	0xe3, 	0x39, 	0x82, 	0x9b, 	0x2f, 	0xff, 	0x87, 	0x34, 	0x8e, 	0x43, 	0x44, 	0xc4, 	0xde, 	0xe9,	0xcb,
/*20*/ 	0x54, 	0x7b, 	0x94, 	0x32, 	0xa6, 	0xc2, 	0x23, 	0x3d, 	0xee, 	0x4c, 	0x95, 	0x0b, 	0x42, 	0xfa, 	0xc3,	0x4e,
/*30*/  0x08, 	0x2e, 	0xa1, 	0x66, 	0x28, 	0xd9, 	0x24, 	0xb2, 	0x76, 	0x5b, 	0xa2, 	0x49, 	0x6d, 	0x8b, 	0xd1,	0x25,
/*40*/ 	0x72, 	0xf8, 	0xf6, 	0x64, 	0x86, 	0x68, 	0x98, 	0x16, 	0xd4, 	0xa4, 	0x5c, 	0xcc, 	0x5d, 	0x65, 	0xb6,	0x92,
/*50*/ 	0x6c, 	0x70, 	0x48, 	0x50, 	0xfd, 	0xed, 	0xb9, 	0xda, 	0x5e, 	0x15, 	0x46, 	0x57, 	0xa7, 	0x8d, 	0x9d,	0x84,
/*60*/ 	0x90, 	0xd8, 	0xab, 	0x00, 	0x8c, 	0xbc, 	0xd3, 	0x0a, 	0xf7, 	0xe4, 	0x58, 	0x05, 	0xb8, 	0xb3, 	0x45,	0x06,
/*70*/ 	0xd0, 	0x2c, 	0x1e, 	0x8f, 	0xca, 	0x3f, 	0x0f, 	0x02, 	0xc1, 	0xaf, 	0xbd, 	0x03, 	0x01, 	0x13, 	0x8a,	0x6b,
/*80*/ 	0x3a, 	0x91, 	0x11, 	0x41, 	0x4f, 	0x67, 	0xdc, 	0xea, 	0x97, 	0xf2, 	0xcf, 	0xce, 	0xf0, 	0xb4, 	0xe6,	0x73,
/*90*/ 	0x96, 	0xac, 	0x74, 	0x22, 	0xe7, 	0xad, 	0x35, 	0x85, 	0xe2, 	0xf9, 	0x37, 	0xe8, 	0x1c, 	0x75, 	0xdf,	0x6e,
/*a0*/ 	0x47, 	0xf1, 	0x1a, 	0x71, 	0x1d, 	0x29, 	0xc5, 	0x89, 	0x6f, 	0xb7, 	0x62, 	0x0e, 	0xaa, 	0x18, 	0xbe,	0x1b,
/*b0*/ 	0xfc, 	0x56, 	0x3e, 	0x4b, 	0xc6, 	0xd2, 	0x79, 	0x20, 	0x9a, 	0xdb, 	0xc0, 	0xfe, 	0x78, 	0xcd, 	0x5a,	0xf4,
/*c0*/ 	0x1f, 	0xdd, 	0xa8, 	0x33, 	0x88, 	0x07, 	0xc7, 	0x31, 	0xb1, 	0x12, 	0x10, 	0x59, 	0x27, 	0x80, 	0xec,	0x5f,
/*d0*/ 	0x60, 	0x51, 	0x7f, 	0xa9, 	0x19, 	0xb5, 	0x4a, 	0x0d, 	0x2d, 	0xe5, 	0x7a, 	0x9f, 	0x93, 	0xc9, 	0x9c,	0xef,
/*e0*/ 	0xa0, 	0xe0, 	0x3b, 	0x4d, 	0xae, 	0x2a, 	0xf5, 	0xb0, 	0xc8, 	0xeb, 	0xbb, 	0x3c, 	0x83, 	0x53, 	0x99,	0x61,
/*f0*/ 	0x17, 	0x2b, 	0x04, 	0x7e, 	0xba, 	0x77, 	0xd6, 	0x26, 	0xe1, 	0x69, 	0x14, 	0x63, 	0x55, 	0x21, 	0x0c,	0x7d };

uint8_t seal[BOXSZ]   = { 71  , 130 , 34  , 219 , 212 , 209 , 24  , 44  , 120 , 11  , 181 , 168 , 223 , 103 , 217 , 220 ,
                          26  , 159 , 73  , 225 , 8   , 197 , 151 , 161 , 233 , 132 , 97  , 226 , 31  , 90  , 137 , 47  ,
                          205 , 22  , 243 , 189 , 50  , 51  , 185 , 110 , 140 , 88  , 231 , 85  , 250 , 145 , 228 , 142 ,
                          182 , 188 , 221 , 74  , 27  , 30  , 86  , 204 , 229 , 94  , 119 , 242 , 37  , 203 , 170 , 213 ,
                          25  , 164 , 201 , 199 , 98  , 171 , 192 , 133 , 191 , 163 , 156 , 234 , 81  , 91  , 33  , 246 ,
                          207 , 19  , 157 , 45  , 167 , 128 , 67  , 241 , 69  , 183 , 172 , 134 , 232 , 148 , 105 , 68  ,
                          2   , 122 , 150 , 12  , 138 , 253 , 76  , 92  , 84  , 210 , 125 , 237 , 146 , 238 , 248 , 208 ,
                          15  , 240 , 75  , 77  , 224 , 106 , 104 , 152 , 127 , 65  , 249 , 211 , 202 , 64  , 109 , 18  ,
                          99  , 123 , 100 , 107 , 196 , 193 , 187 , 184 , 255 , 70  , 38  , 59  , 190 , 129 , 200 , 160 ,
                          3   , 82  , 40  , 195 , 55  , 63  , 79  , 89  , 53  , 87  , 239 , 54  , 173 , 251 , 43  , 147 ,
                          23  , 57  , 95  , 56  , 42  , 0   , 113 , 141 , 36  , 136 , 186 , 39  , 121 , 29  , 6   , 32  ,
                          7   , 48  , 161 , 46  , 4   , 72  , 214 , 215 , 78  , 230 , 83  , 247 , 131 , 126 , 58  , 114 ,
                          96  , 180 , 20  , 17  , 28  , 93  , 1   , 9   , 111 , 162 , 124 , 41  , 245 , 252 , 52  , 216 ,
                          14  , 102 , 254 , 108 , 175 , 154 , 10  , 16  , 206 , 117 , 244 , 218 , 62  , 21  , 35  , 66  ,
                          179 , 5   , 144 , 80  , 116 , 176 , 198 , 101 , 155 , 194 , 13  , 236 , 158 , 135 , 166 , 169 ,
                          227 , 235 , 165 , 115 , 222 , 112 , 49  , 178 , 174 , 60  , 153 , 118 , 139 , 177 , 143 , 149 };
                      
uint8_t unseal[BOXSZ] = { 165 , 198 , 96  , 144 , 180 , 225 , 174 , 176 , 20  , 199 , 214 , 9   , 99  , 234 , 208 , 112 , 
			  215 , 195 , 127 , 81  , 194 , 221 , 33  , 160 , 6   , 64  , 16  , 52  , 196 , 173 , 53  , 28  , 
			  175 , 78  , 2   , 222 , 168 , 60  , 138 , 171 , 146 , 203 , 164 , 158 , 7   , 83  , 179 , 31  , 
			  177 , 246 , 36  , 37  , 206 , 152 , 155 , 148 , 163 , 161 , 190 , 139 , 249 , 0   , 220 , 149 , 
			  125 , 121 , 223 , 86  , 95  , 88  , 137 , 0   , 181 , 18  , 51  , 114 , 102 , 115 , 184 , 150 , 
			  227 , 76  , 145 , 186 , 104 , 43  , 54  , 153 , 41  , 151 , 29  , 77  , 103 , 197 , 57  , 162 , 
			  192 , 26  , 68  , 128 , 130 , 231 , 209 , 13  , 118 , 94  , 117 , 131 , 211 , 126 , 39  , 200 , 
			  245 , 166 , 191 , 243 , 228 , 217 , 251 , 58  , 8   , 172 , 97  , 129 , 202 , 106 , 189 , 120 , 
			  85  , 141 , 1   , 188 , 25  , 71  , 91  , 237 , 169 , 30  , 100 , 252 , 40  , 167 , 47  , 254 , 
			  226 , 45  , 108 , 159 , 93  , 255 , 98  , 22  , 119 , 250 , 213 , 232 , 74  , 82  , 236 , 17  , 
			  143 , 178 , 201 , 73  , 65  , 242 , 238 , 84  , 11  , 239 , 62  , 69  , 90  , 156 , 248 , 212 , 
			  229 , 253 , 247 , 224 , 193 , 10  , 48  , 89  , 135 , 38  , 170 , 134 , 49  , 35  , 140 , 72  , 
			  70  , 133 , 233 , 147 , 132 , 21  , 230 , 67  , 142 , 66  , 124 , 61  , 55  , 32  , 216 , 80  , 
			  111 , 5   , 105 , 123 , 4   , 63  , 182 , 183 , 207 , 14  , 219 , 3   , 15  , 50  , 244 , 12  , 
			  116 , 19  , 27  , 240 , 46  , 56  , 185 , 42  , 92  , 24  , 75  , 241 , 235 , 107 , 109 , 154 , 
			  113 , 87  , 59  , 34  , 218 , 204 , 79  , 187 , 110 , 122 , 44  , 157 , 205 , 101 , 210 , 136 };
                      
uint8_t darkofnight[BOXSZ] = { 130 , 181 , 146 , 11  , 143 , 99  , 155 , 89  , 201 , 87  , 27  , 158 , 202 , 16  , 153 , 157 , 
			       165 , 206 , 248 , 178 , 10  , 44  , 237 , 7   , 5   , 247 , 119 , 208 , 73  , 40  , 31  , 232 , 
			       184 , 29  , 90  , 207 , 82  , 57  , 145 , 141 , 219 , 170 , 32  , 144 , 148 , 172 , 15  , 140 , 
			       97  , 188 , 42  , 41  , 118 , 107 , 228 , 253 , 111 , 204 , 62  , 17  , 242 , 189 , 183 , 231 , 
			       154 , 46  , 126 , 180 , 200 , 229 , 167 , 92  , 56  , 109 , 129 , 96  , 100 , 70  , 195 , 169 , 
			       198 , 187 , 245 , 18  , 149 , 142 , 222 , 30  , 71  , 84  , 210 , 80  , 35  , 177 , 19  , 213 , 
			       103 , 234 , 134 , 246 , 36  , 239 , 128 , 139 , 74  , 9   , 135 , 226 , 131 , 218 , 216 , 116 , 
			       104 , 255 , 243 , 25  , 51  , 168 , 34  , 233 , 28  , 161 , 33  , 179 , 251 , 48  , 61  , 65  , 
			       236 , 196 , 182 , 175 , 138 , 209 , 101 , 102 , 132 , 230 , 85  , 215 , 123 , 164 , 150 , 55  , 
			       162 , 192 , 199 , 93  , 203 , 124 , 45  , 37  , 244 , 75  , 79  , 83  , 249 , 24  , 13  , 94  , 
			       220 , 8   , 64  , 174 , 117 , 53  , 38  , 122 , 121 , 95  , 240 , 112 , 193 , 22  , 63  , 254 , 
			       136 , 238 , 171 , 190 , 78  , 60  , 137 , 1   , 2   , 52  , 176 , 14  , 194 , 185 , 147 , 156 , 
			       20  , 86  , 235 , 76  , 12  , 98  , 217 , 127 , 163 , 39  , 205 , 115 , 23  , 191 , 197 , 211 , 
			       110 , 69  , 66  , 173 , 160 , 241 , 108 , 47  , 250 , 133 , 91  , 43  , 212 , 21  , 106 , 151 , 
			       54  , 88  , 114 , 214 , 227 , 152 , 67  , 0   , 72  , 225 , 105 , 26  , 50  , 221 , 113 , 3   , 
			       4   , 6   , 59  , 68  , 77  , 223 , 58  , 186 , 81  , 125 , 252 , 166 , 159 , 49  , 224 , 120 };

uint8_t lightofday[BOXSZ]  = { 231 , 183 , 184 , 239 , 240 , 24  , 241 , 23  , 161 , 105 , 20  , 3   , 196 , 158 , 187 , 46  , 
			       13  , 59  , 83  , 94  , 192 , 221 , 173 , 204 , 157 , 115 , 235 , 10  , 120 , 33  , 87  , 30  , 
			       42  , 122 , 118 , 92  , 100 , 151 , 166 , 201 , 29  , 51  , 50  , 219 , 21  , 150 , 65  , 215 , 
			       125 , 253 , 236 , 116 , 185 , 165 , 224 , 143 , 72  , 37  , 246 , 242 , 181 , 126 , 58  , 174 , 
			       162 , 127 , 210 , 230 , 243 , 209 , 77  , 88  , 232 , 28  , 104 , 153 , 195 , 244 , 180 , 154 , 
			       91  , 248 , 36  , 155 , 89  , 138 , 193 , 9   , 225 , 7   , 34  , 218 , 71  , 147 , 159 , 169 , 
			       75  , 48  , 197 , 5   , 76  , 134 , 135 , 96  , 112 , 234 , 222 , 53  , 214 , 73  , 208 , 56  , 
			       171 , 238 , 226 , 203 , 111 , 164 , 52  , 26  , 255 , 168 , 167 , 140 , 149 , 249 , 66  , 199 , 
			       102 , 74  , 0   , 108 , 136 , 217 , 98  , 106 , 176 , 182 , 132 , 103 , 47  , 39  , 85  , 4   , 
			       43  , 38  , 2   , 190 , 44  , 84  , 142 , 223 , 229 , 14  , 64  , 6   , 191 , 15  , 11  , 252 , 
			       212 , 121 , 144 , 200 , 141 , 16  , 251 , 70  , 117 , 79  , 41  , 178 , 45  , 211 , 163 , 131 , 
			       186 , 93  , 19  , 123 , 67  , 1   , 130 , 62  , 32  , 189 , 247 , 81  , 49  , 61  , 179 , 205 , 
			       145 , 172 , 188 , 78  , 129 , 206 , 80  , 146 , 68  , 8   , 12  , 148 , 57  , 202 , 17  , 35  , 
			       27  , 133 , 90  , 207 , 220 , 95  , 227 , 139 , 110 , 198 , 109 , 40  , 160 , 237 , 86  , 245 , 
			       254 , 233 , 107 , 228 , 54  , 69  , 137 , 63  , 31  , 119 , 97  , 194 , 128 , 22  , 177 , 101 , 
			       170 , 213 , 60  , 114 , 152 , 82  , 99  , 25  , 18  , 156 , 216 , 124 , 250 , 55  , 175 , 113 };

#define TRANSPOSE(reg) 	((*(aes + (reg))))
#define TRANSLATE(reg) 	((*(aesinv + (reg))))

#define SEAL(reg)   	((*(seal + (reg))))
#define UNSEAL(reg) 	((*(unseal + (reg))))

#define DARKNESS(reg)   ((*(darkofnight + (reg))))
#define LIGHT(reg) 	((*(lightofday + (reg))))

#define DYNAMICBOX(box, reg)    ((*((box) + (reg))))

#define FIRSTHALF_MASK  0b00001111
#define SECONDHALF_MASK 0b11110000

#define FIRSTQTR_MASK  0b00000011
#define SECONDQTR_MASK 0b00001100
#define THIRDQTR_MASK  0b00110000
#define FOURTHQTR_MASK 0b11000000

#define FIRSTHALF(reg)  		(FIRSTHALF_MASK  & (reg))
#define SECONDHALF(reg) 		(SECONDHALF_MASK & (reg))

// 12 and 21 indicate bits format from binary direction perspective (not array direction)
#define COMBINEHALVES12(reg1, reg2)	((SECONDHALF(reg1)) | (FIRSTHALF(reg2)))
#define COMBINEHALVES21(reg1, reg2)	((SECONDHALF(reg2)) | (FIRSTHALF(reg1)))
static inline void POSITION_HALFBYTES_FROM12(uint8_t* byte1, uint8_t* byte2, uint8_t halves)
{
	*byte1 = COMBINEHALVES12(halves, *byte1);
	*byte2 = COMBINEHALVES12(*byte2, halves);
}
static inline void POSITION_HALFBYTES_FROM21(uint8_t* byte1, uint8_t* byte2, uint8_t halves)
{
	*byte2 = COMBINEHALVES21(*byte2, halves);
	*byte1 = COMBINEHALVES21(halves, *byte1);
}

// Weave top part of first byte and bottom part of second byte together
static inline void switchlock12(uint8_t* blackbox, uint8_t* byte1, uint8_t* byte2)
{
	register uint8_t halves = COMBINEHALVES12(*byte1, *byte2);
			 halves = DYNAMICBOX(box, halves);
	POSITION_HALFBYTES_FROM12(byte1, byte2, halves);
}
// Weave bottom part of first byte and top part of second byte together
static inline void switchlock21(uint8_t* blackbox, uint8_t* byte1, uint8_t* byte2)
{
	register uint8_t halves = permute8bits(COMBINEHALVES21(*byte1, *byte2));
			 halves = DYNAMICBOX(box, halves);
	POSITION_HALFBYTES_FROM21(byte1, byte2, halves);
}

/*
// MATRIX FROM AES
unsigned long long int mix[MIXERSZ] = { 0x0000000000000002, 0x0000000000000003, 0x0000000000000001, 0x0000000000000001, 
			      		0x0000000000000001, 0x0000000000000002, 0x0000000000000003, 0x0000000000000001, 
			       		0x0000000000000001, 0x0000000000000001, 0x0000000000000002, 0x0000000000000003, 
			       		0x0000000000000003, 0x0000000000000001, 0x0000000000000001, 0x0000000000000002, };
// INVERSE MATRIX FROM AES
unsigned long long int demix[MIXERSZ] = { 0x000000000000000e, 0x000000000000000b, 0x000000000000000d, 0x0000000000000009, 
			         	  0x0000000000000009, 0x000000000000000e, 0x000000000000000b, 0x000000000000000d, 
			         	  0x000000000000000d, 0x0000000000000009, 0x000000000000000e, 0x000000000000000b, 
			         	  0x000000000000000b, 0x000000000000000d, 0x0000000000000009, 0x000000000000000e, };
			         	  
char bytemult(uint8_t first, uint8_t arrval)	// Executes Galois Field Multiplication [Only applicable to AES]
{
	first &= 0x00000000000000ff;
	arrval &= 0x00000000000000ff;
	char f = 0;
	if (arrval == 0x01)	  // If 1
		return first;
	else if (arrval == 0x02)  // If x
	{
		f = 0b10000000 & first;
		first <<= 1;
		if (f) return first ^ 0b00011011;
		else   return first ^ 0b00000000;
	}	
	else if (arrval == 0x03)  // If x+1
		return first ^ bytemult(first, 2);	
	else if (arrval == 0x09)  // Inverse
		return first ^ bytemult(bytemult(bytemult(first, 2), 2), 2);
	else if (arrval == 0x0b)  // Inverse
		return first ^ bytemult(first ^ bytemult(bytemult(first, 2), 2), 2);
	else if (arrval == 0x0d)  // Inverse
		return first ^ bytemult(bytemult(first ^ bytemult(first, 2), 2), 2);
	else if (arrval == 0x0e)  // Inverse
		return bytemult(first ^ bytemult(first ^ bytemult(first, 2), 2), 2);
	else
		THROW("ARRAY VALUE ERROR: only 0x01, 0x02, 0x03, 0x09, 0x0b, 0x0d, and 0x0e allowed");
	return 0; // Unreachable
}

char bytesubadd(uint8_t first, uint8_t second) { return (0x00000000000000ff & first) ^ (0x00000000000000ff & second); }

*/

void sow(uint64_t* x, uint64_t* k, uint64_t decree)
{
	register uint64_t C     = *k; 	//5514838803201;
	register uint64_t faith = 0b0000000000000000000000000000000000000000000000000000000000000000 | (decree << 48);	// Places decree value into 6th byte
	
	switch(decree % 7)
	{
		case 0 : ;
			 faith = GETBYTE0_ASBYTE4(C) |
			 	 GETBYTE4_ASBYTE1(C) |
			 	 GETBYTE1_ASBYTE5(C) |
			 	 GETBYTE5_ASBYTE2(C) |
			 	 GETBYTE2_ASBYTE6(C) |
			 	 GETBYTE6_ASBYTE3(C) ^
			 	 GETBYTE3_ASBYTE0(C);
			 break;
		case 1 : ;
			 faith = GETBYTE0(C) |
			 	 GETBYTE1(C) |
			 	 GETBYTE2(C) |
			 	 GETBYTE3(C) |
			 	 GETBYTE4(C) |
			 	 GETBYTE5(C) ^
			 	 GETBYTE6(C);
			 break;
		case 2 : ;
			 faith = GETBYTE0_ASBYTE5(C) |
			 	 GETBYTE5_ASBYTE3(C) |
			 	 GETBYTE3_ASBYTE1(C) |
			 	 GETBYTE1_ASBYTE6(C) |
			 	 GETBYTE6_ASBYTE4(C) |
			 	 GETBYTE4_ASBYTE2(C) ^
			 	 GETBYTE2_ASBYTE0(C);
			 break;
		case 3 : ;
			 faith = GETBYTE0_ASBYTE2(C) |
			 	 GETBYTE2_ASBYTE4(C) |
			 	 GETBYTE4_ASBYTE6(C) |
			 	 GETBYTE6_ASBYTE1(C) |
			 	 GETBYTE1_ASBYTE3(C) |
			 	 GETBYTE3_ASBYTE5(C) ^
			 	 GETBYTE5_ASBYTE0(C);
			 break;
		case 4 : ;
			 faith = GETBYTE0_ASBYTE6(C) |
			 	 GETBYTE6_ASBYTE5(C) |
			 	 GETBYTE5_ASBYTE4(C) |
			 	 GETBYTE4_ASBYTE3(C) |
			 	 GETBYTE3_ASBYTE2(C) |
			 	 GETBYTE2_ASBYTE1(C) ^
			 	 GETBYTE1_ASBYTE0(C);
			 break;
		case 5 : ;
			 faith = GETBYTE0_ASBYTE6(C) |
			 	 GETBYTE6_ASBYTE5(C) |
			 	 GETBYTE5_ASBYTE4(C) |
			 	 GETBYTE4_ASBYTE3(C) |
			 	 GETBYTE3_ASBYTE2(C) |
			 	 GETBYTE2_ASBYTE1(C) ^
			 	 GETBYTE1_ASBYTE0(C);
			 break;
		case 6 : ;
			 faith = GETBYTE0_ASBYTE3(C) |
			 	 GETBYTE3_ASBYTE6(C) |
			 	 GETBYTE6_ASBYTE2(C) |
			 	 GETBYTE2_ASBYTE5(C) |
			 	 GETBYTE5_ASBYTE1(C) |
			 	 GETBYTE1_ASBYTE4(C) ^
			 	 GETBYTE4_ASBYTE0(C);
	}
	*x ^= faith;
}

void til(uint64_t* x, uint64_t* y, uint64_t* z)
{
	register uint64_t regx = *x;
	register uint64_t regy = *y;
	register uint64_t regz = *z;
	
	*x = regx ^ regy;
	*y = regy ^ regz;
	*z = regz ^ regx;
}

void weave(uint8_t* field, uint8_t k)
{
	// 0,0
}

void weaver(uint8_t* field, uint8_t k)
{
	// 0 3 6 2 5 1 4
	// 4 1 5 2 6 3 0
	uint64_t* ptr0 = (uint64_t*)(field);
	uint64_t* ptr1 = (uint64_t*)(field + 7);
	uint64_t* ptr2 = (uint64_t*)(field + 14);
	uint64_t* ptr3 = (uint64_t*)(field + 21);
	uint64_t* ptr4 = (uint64_t*)(field + 28);
	uint64_t* ptr5 = (uint64_t*)(field + 35);
	uint64_t* ptr6 = (uint64_t*)(field + 42);
	register uint64_t area0 = *ptr0;
	register uint64_t area1 = *ptr1;
	register uint64_t area2 = *ptr2;
	register uint64_t area3 = *ptr3;
	register uint64_t area4 = *ptr4;
	register uint64_t area5 = *ptr5;
	register uint64_t area6 = *ptr6;
	
//	ptr0 = GETBYTE();
//	ptr1 = GETBYTE0(area4) ^ GETBYTE3(area1) ^ GETBYTE6(area5) ^ GETBYTE2(area2) ^ GETBYTE5(area6) ^ GETBYTE1(area3) ^ GETBYTE4(area0);
//	ptr2 = GETBYTE0(area0) ^ GETBYTE3(area3) ^ GETBYTE6(area6) ^ GETBYTE2(area2) ^ GETBYTE5(area5) ^ GETBYTE1(area1) ^ GETBYTE4(area4);
//	ptr3 = GETBYTE0(area0) ^ GETBYTE3(area3) ^ GETBYTE6(area6) ^ GETBYTE2(area2) ^ GETBYTE5(area5) ^ GETBYTE1(area1) ^ GETBYTE4(area4);
//	ptr4 = GETBYTE0(area4) ^ GETBYTE3(area1) ^ GETBYTE6(area5) ^ GETBYTE2(area2) ^ GETBYTE5(area6) ^ GETBYTE1(area3) ^ GETBYTE4(area0);
//	ptr5 = GETBYTE4(area4) ^ GETBYTE0(area0) ^ GETBYTE6(area6) ^ GETBYTE2(area2) ^ GETBYTE5(area5) ^ GETBYTE1(area1) ^ GETBYTE4(area4);
//	ptr6 = GETBYTE0(area0) ^ GETBYTE3(area3) ^ GETBYTE6(area6) ^ GETBYTE2(area2) ^ GETBYTE5(area5) ^ GETBYTE1(area1) ^ GETBYTE4(area4);

	
	// 0 3 6 2 5 1 4
	register uint8_t S = k;
	
}

void flesh(uint64_t* x)
{
	register uint64_t hold = *x;
	register uint64_t work = TRANSPOSE(GETBYTE0(hold)) | 
				 TRANSPOSE(GETBYTE1(hold)) | 
				 TRANSPOSE(GETBYTE2(hold)) | 
				 TRANSPOSE(GETBYTE3(hold)) | 
				 TRANSPOSE(GETBYTE4(hold)) | 
				 TRANSPOSE(GETBYTE5(hold)) | 
				 TRANSPOSE(GETBYTE6(hold)) | 
				 TRANSPOSE(GETBYTE7(hold));
	*x = work;
}
void stone(uint64_t* x)
{
	register uint64_t hold = *x;
	register uint64_t work = TRANSLATE(GETBYTE0(hold)) | 
				 TRANSLATE(GETBYTE1(hold)) | 
				 TRANSLATE(GETBYTE2(hold)) | 
				 TRANSLATE(GETBYTE3(hold)) | 
				 TRANSLATE(GETBYTE4(hold)) | 
				 TRANSLATE(GETBYTE5(hold)) | 
				 TRANSLATE(GETBYTE6(hold)) | 
				 TRANSLATE(GETBYTE7(hold));
	*x = work;
}




#endif // _CRYPT_
