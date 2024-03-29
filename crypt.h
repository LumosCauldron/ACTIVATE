#ifndef _CRYPT_
#define _CRYPT_

#include "bits.h"
#include "hash.h"
#include <math.h>


// SBOX FROM AES
//u8 aes[BOXSZ] = 
// 	00 	01 	02 	03 	04 	05 	06 	07 	08 	09 	0a 	0b 	0c 	0d 	0e 	0f
/*00*///{	0x63, 	0x7c, 	0x77, 	0x7b, 	0xf2, 	0x6b, 	0x6f, 	0xc5, 	0x30, 	0x01, 	0x67, 	0x2b, 	0xfe, 	0xd7, 	0xab, 	0x76,
/*10*/// 	0xca, 	0x82, 	0xc9, 	0x7d, 	0xfa, 	0x59, 	0x47, 	0xf0, 	0xad, 	0xd4, 	0xa2, 	0xaf, 	0x9c, 	0xa4, 	0x72, 	0xc0,
/*20*///        0xb7, 	0xfd, 	0x93, 	0x26, 	0x36, 	0x3f, 	0xf7, 	0xcc, 	0x34, 	0xa5, 	0xe5, 	0xf1, 	0x71, 	0xd8, 	0x31, 	0x15,
/*30*/// 	0x04, 	0xc7, 	0x23, 	0xc3, 	0x18, 	0x96, 	0x05, 	0x9a, 	0x07, 	0x12, 	0x80, 	0xe2, 	0xeb, 	0x27, 	0xb2, 	0x75,
/*40*/// 	0x09,	0x83, 	0x2c, 	0x1a, 	0x1b, 	0x6e, 	0x5a, 	0xa0, 	0x52, 	0x3b, 	0xd6, 	0xb3, 	0x29, 	0xe3, 	0x2f, 	0x84,
/*50*/// 	0x53, 	0xd1, 	0x00, 	0xed, 	0x20, 	0xfc, 	0xb1, 	0x5b, 	0x6a, 	0xcb, 	0xbe, 	0x39, 	0x4a, 	0x4c, 	0x58, 	0xcf,
/*60*/// 	0xd0, 	0xef, 	0xaa, 	0xfb, 	0x43, 	0x4d, 	0x33, 	0x85, 	0x45, 	0xf9, 	0x02, 	0x7f, 	0x50, 	0x3c, 	0x9f, 	0xa8,
/*70*/// 	0x51, 	0xa3, 	0x40, 	0x8f, 	0x92, 	0x9d, 	0x38, 	0xf5, 	0xbc, 	0xb6, 	0xda, 	0x21, 	0x10, 	0xff, 	0xf3, 	0xd2,
/*80*/// 	0xcd, 	0x0c, 	0x13, 	0xec, 	0x5f, 	0x97, 	0x44, 	0x17, 	0xc4, 	0xa7, 	0x7e, 	0x3d, 	0x64, 	0x5d, 	0x19, 	0x73,
/*90*/// 	0x60, 	0x81, 	0x4f, 	0xdc, 	0x22, 	0x2a, 	0x90, 	0x88, 	0x46, 	0xee, 	0xb8, 	0x14, 	0xde, 	0x5e, 	0x0b, 	0xdb,
/*a0*/// 	0xe0, 	0x32, 	0x3a, 	0x0a, 	0x49, 	0x06, 	0x24, 	0x5c, 	0xc2, 	0xd3, 	0xac, 	0x62, 	0x91, 	0x95, 	0xe4, 	0x79,
/*b0*/// 	0xe7, 	0xc8, 	0x37, 	0x6d, 	0x8d, 	0xd5, 	0x4e, 	0xa9, 	0x6c, 	0x56, 	0xf4, 	0xea, 	0x65, 	0x7a, 	0xae, 	0x08,
/*c0*/// 	0xba, 	0x78, 	0x25, 	0x2e, 	0x1c, 	0xa6, 	0xb4, 	0xc6, 	0xe8, 	0xdd, 	0x74, 	0x1f, 	0x4b, 	0xbd, 	0x8b, 	0x8a,
/*d0*/// 	0x70, 	0x3e, 	0xb5, 	0x66, 	0x48, 	0x03, 	0xf6, 	0x0e, 	0x61, 	0x35, 	0x57, 	0xb9, 	0x86, 	0xc1, 	0x1d, 	0x9e,
/*e0*/// 	0xe1, 	0xf8, 	0x98, 	0x11, 	0x69, 	0xd9, 	0x8e, 	0x94, 	0x9b, 	0x1e, 	0x87, 	0xe9, 	0xce, 	0x55, 	0x28, 	0xdf,
/*f0*/// 	0x8c, 	0xa1, 	0x89, 	0x0d, 	0xbf, 	0xe6, 	0x42, 	0x68, 	0x41, 	0x99, 	0x2d, 	0x0f, 	0xb0, 	0x54, 	0xbb, 	0x16 }; 
// INVERSE SBOX FROM AES
//u8 aesinv[BOXSZ] =
// 	00 	01 	02 	03 	04 	05 	06 	07 	08 	09 	0a 	0b 	0c 	0d 	0e 	0f
/*00*///{       0x52, 	0x09, 	0x6a, 	0xd5, 	0x30, 	0x36, 	0xa5, 	0x38, 	0xbf, 	0x40, 	0xa3, 	0x9e, 	0x81, 	0xf3, 	0xd7, 	0xfb,
/*10*/// 	0x7c, 	0xe3, 	0x39, 	0x82, 	0x9b, 	0x2f, 	0xff, 	0x87, 	0x34, 	0x8e, 	0x43, 	0x44, 	0xc4, 	0xde, 	0xe9,	0xcb,
/*20*/// 	0x54, 	0x7b, 	0x94, 	0x32, 	0xa6, 	0xc2, 	0x23, 	0x3d, 	0xee, 	0x4c, 	0x95, 	0x0b, 	0x42, 	0xfa, 	0xc3,	0x4e,
/*30*///        0x08, 	0x2e, 	0xa1, 	0x66, 	0x28, 	0xd9, 	0x24, 	0xb2, 	0x76, 	0x5b, 	0xa2, 	0x49, 	0x6d, 	0x8b, 	0xd1,	0x25,
/*40*/// 	0x72, 	0xf8, 	0xf6, 	0x64, 	0x86, 	0x68, 	0x98, 	0x16, 	0xd4, 	0xa4, 	0x5c, 	0xcc, 	0x5d, 	0x65, 	0xb6,	0x92,
/*50*/// 	0x6c, 	0x70, 	0x48, 	0x50, 	0xfd, 	0xed, 	0xb9, 	0xda, 	0x5e, 	0x15, 	0x46, 	0x57, 	0xa7, 	0x8d, 	0x9d,	0x84,
/*60*/// 	0x90, 	0xd8, 	0xab, 	0x00, 	0x8c, 	0xbc, 	0xd3, 	0x0a, 	0xf7, 	0xe4, 	0x58, 	0x05, 	0xb8, 	0xb3, 	0x45,	0x06,
/*70*/// 	0xd0, 	0x2c, 	0x1e, 	0x8f, 	0xca, 	0x3f, 	0x0f, 	0x02, 	0xc1, 	0xaf, 	0xbd, 	0x03, 	0x01, 	0x13, 	0x8a,	0x6b,
/*80*/// 	0x3a, 	0x91, 	0x11, 	0x41, 	0x4f, 	0x67, 	0xdc, 	0xea, 	0x97, 	0xf2, 	0xcf, 	0xce, 	0xf0, 	0xb4, 	0xe6,	0x73,
/*90*/// 	0x96, 	0xac, 	0x74, 	0x22, 	0xe7, 	0xad, 	0x35, 	0x85, 	0xe2, 	0xf9, 	0x37, 	0xe8, 	0x1c, 	0x75, 	0xdf,	0x6e,
/*a0*/// 	0x47, 	0xf1, 	0x1a, 	0x71, 	0x1d, 	0x29, 	0xc5, 	0x89, 	0x6f, 	0xb7, 	0x62, 	0x0e, 	0xaa, 	0x18, 	0xbe,	0x1b,
/*b0*/// 	0xfc, 	0x56, 	0x3e, 	0x4b, 	0xc6, 	0xd2, 	0x79, 	0x20, 	0x9a, 	0xdb, 	0xc0, 	0xfe, 	0x78, 	0xcd, 	0x5a,	0xf4,
/*c0*/// 	0x1f, 	0xdd, 	0xa8, 	0x33, 	0x88, 	0x07, 	0xc7, 	0x31, 	0xb1, 	0x12, 	0x10, 	0x59, 	0x27, 	0x80, 	0xec,	0x5f,
/*d0*/// 	0x60, 	0x51, 	0x7f, 	0xa9, 	0x19, 	0xb5, 	0x4a, 	0x0d, 	0x2d, 	0xe5, 	0x7a, 	0x9f, 	0x93, 	0xc9, 	0x9c,	0xef,
/*e0*/// 	0xa0, 	0xe0, 	0x3b, 	0x4d, 	0xae, 	0x2a, 	0xf5, 	0xb0, 	0xc8, 	0xeb, 	0xbb, 	0x3c, 	0x83, 	0x53, 	0x99,	0x61,
/*f0*/// 	0x17, 	0x2b, 	0x04, 	0x7e, 	0xba, 	0x77, 	0xd6, 	0x26, 	0xe1, 	0x69, 	0x14, 	0x63, 	0x55, 	0x21, 	0x0c,	0x7d };
/*
u8 seal[BOXSZ]   =      { 71  , 130 , 34  , 219 , 212 , 209 , 24  , 44  , 120 , 11  , 181 , 168 , 223 , 103 , 217 , 220 ,
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
u8 unseal[BOXSZ] =      { 165 , 198 , 96  , 144 , 180 , 225 , 174 , 176 , 20  , 199 , 214 , 9   , 99  , 234 , 208 , 112 , 
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
u8 darkofnight[BOXSZ] = { 130 , 181 , 146 , 11  , 143 , 99  , 155 , 89  , 201 , 87  , 27  , 158 , 202 , 16  , 153 , 157 , 
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
u8 lightofday[BOXSZ]  = { 231 , 183 , 184 , 239 , 240 , 24  , 241 , 23  , 161 , 105 , 20  , 3   , 196 , 158 , 187 , 46  , 
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
			  
#define TRANSPOSE(reg) ((*(aes + (reg))))
#define TRANSLATE(reg) ((*(aesinv + (reg))))
#define SEAL(reg)      ((*(seal + (reg))))
#define UNSEAL(reg)    ((*(unseal + (reg))))
#define DARKNESS(reg)  ((*(darkofnight + (reg))))
#define LIGHT(reg)     ((*(lightofday + (reg))))
*/
#define BOXSZ    	256
#define MSGBLKSZ  	 49
#define KEYSZ     	 21
#define BLKBLKSZ   	  7
#define KEYBLKSZ   	  7
#define ROUNDCOUNT 	 21
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

u8  lineup[KEYSZ * ROUNDCOUNT];
u8  sboxarray[ROUNDCOUNT * BOXSZ * 2];
u8* F_i_E_L_D = NULLPTR;

u64  G	   = 0x0000000000000000;
u64  S	   = 0x0000000000000000;
u64  H	   = 0x0000000000000000;
u64  hG    = 0x0000000000000000;
u64  hS    = 0x0000000000000000;
u64  hH    = 0x0000000000000000;
u32  GSHh  = 0x00000000;
u32  Gh    = 0x00000000;
u32  Sh    = 0x00000000;
u32  Hh    = 0x00000000;
u8   order = 0x00;

static inline void keytoreg(u8* ptr)	// Overwrites 'hG', 'hS', and 'hH'
{
	u64* kptr1 = (u64*)(ptr); 
	u64* kptr2 = (u64*)(ptr + BLKBLKSZ); 
	u64* kptr3 = (u64*)(ptr + BLKBLKSZ + BLKBLKSZ); 	
		hG = CLEARBYTE7(*kptr1);
		hS = CLEARBYTE7(*kptr2);
		hH = CLEARBYTE7(*kptr3);
}

static inline void regtokey(u8* ptr)	// Overwrites 'hG', 'hS', and 'hH'
{
	u64* kptr1 = (u64*)(ptr); 
	u64* kptr2 = (u64*)(ptr + BLKBLKSZ); 
	u64* kptr3 = (u64*)(ptr + BLKBLKSZ + BLKBLKSZ); 	
	*kptr1 = hG;
	*kptr2 = hS;
	*kptr3 = hH;
}

static inline void POSITION_HALFBYTES_FROM12(u8* byte1, u8* byte2, u8 halves)
{
	*byte1 = COMBINEHALVES12(halves, *byte1);
	*byte2 = COMBINEHALVES12(*byte2, halves);
}
static inline void POSITION_HALFBYTES_FROM21(u8* byte1, u8* byte2, u8 halves)
{
	*byte2 = COMBINEHALVES21(*byte2, halves);
	*byte1 = COMBINEHALVES21(halves, *byte1);
}

// Weave top part of first byte and bottom part of second byte together
static inline void switchlock12(u8* blackbox, u8* byte1, u8* byte2)
{
	register u8 halves = permute8bits_byte0(COMBINEHALVES12(*byte1, *byte2));
		    halves = DYNAMICBOX(blackbox, halves);
	POSITION_HALFBYTES_FROM12(byte1, byte2, halves);
}
// Weave bottom part of first byte and top part of second byte together
static inline void switchlock21(u8* blackbox, u8* byte1, u8* byte2)
{
	register u8 halves = unify8bits_byte0(COMBINEHALVES21(*byte1, *byte2));
		    halves = DYNAMICBOX(blackbox, halves);
	POSITION_HALFBYTES_FROM21(byte1, byte2, halves);
}

static inline void setkey(u8* trikey)	// Determine order, determine & hide hashes, and hide order
{
	order = *(trikey + MOD(*(trikey)      + *(trikey +  1) + *(trikey +  2) + *(trikey +  3) + *(trikey +  4) + *(trikey +  5) + *(trikey +  6) +
		   	       *(trikey +  7) + *(trikey +  8) + *(trikey +  9) + *(trikey + 10) + *(trikey + 11) + *(trikey + 12) + *(trikey + 13) +
		   	       *(trikey + 14) + *(trikey + 15) + *(trikey + 16) + *(trikey + 17) + *(trikey + 18) + *(trikey + 19) + *(trikey + 20), KEYSZ));
	
	u64* kptr1 = (u64*)(trikey); 
	u64* kptr2 = (u64*)(trikey + BLKBLKSZ); 
	u64* kptr3 = (u64*)(trikey + BLKBLKSZ + BLKBLKSZ); 
	switch(order % 3)
	{
		case 0:	
			G    = CLEARBYTE7(*kptr1);
			S    = CLEARBYTE7(*kptr2);
			H    = CLEARBYTE7(*kptr3);
			Gh   = MOD(order * signature((const char*)kptr1, BLKBLKSZ), 0x100000000);
			Sh   = MOD(order * signature((const char*)kptr2, BLKBLKSZ), 0x100000000);
			Hh   = MOD(order * signature((const char*)kptr3, BLKBLKSZ), 0x100000000);
			break;
		case 1:
			G    = CLEARBYTE7(*kptr2);
			S    = CLEARBYTE7(*kptr3);
			H    = CLEARBYTE7(*kptr1);
			Gh   = MOD(order * signature((const char*)kptr2, BLKBLKSZ), 0x100000000);
			Sh   = MOD(order * signature((const char*)kptr3, BLKBLKSZ), 0x100000000);
			Hh   = MOD(order * signature((const char*)kptr1, BLKBLKSZ), 0x100000000);
			break;
		case 2:
			G    = CLEARBYTE7(*kptr3);
			S    = CLEARBYTE7(*kptr1);
			H    = CLEARBYTE7(*kptr2);
			Gh   = MOD(order * signature((const char*)kptr3, BLKBLKSZ), 0x100000000);
			Sh   = MOD(order * signature((const char*)kptr1, BLKBLKSZ), 0x100000000);
			Hh   = MOD(order * signature((const char*)kptr2, BLKBLKSZ), 0x100000000); // 4,294,967,296
	}
	GSHh  = signature(trikey, KEYSZ);
	order = MOD(order + GSHh + Gh + Sh + Hh, 0x100); // 256
}

static inline void boxgen(u32 qubo)
{
	register float u = 0.00000000;
	register float g = 0.00000000;
	register float v = 0.00000000;
	register u8    x = 0;
	switch(order % 4)
	{
		case 0 : ;
			u = GETBYTE0(qubo);
			g = GETBYTE1(qubo);
			v = GETBYTE2(qubo);
			x = GETBYTE3(qubo);
		break;
		case 1 : ;
			u = GETBYTE1(qubo);
			g = GETBYTE2(qubo);
			v = GETBYTE3(qubo);
			x = GETBYTE0(qubo);
		break;
		case 2 : ;
			u = GETBYTE2(qubo);
			g = GETBYTE3(qubo);
			v = GETBYTE0(qubo);
			x = GETBYTE1(qubo);
		break;
		case 3 : ;
			u = GETBYTE3(qubo);
			g = GETBYTE0(qubo);
			v = GETBYTE1(qubo);
			x = GETBYTE2(qubo);
	}

	register float phi   = 1.6180000;
	register float pi    = 3.1410000;
	register float e     = 2.7180000;
	register u16 i          = 0;
	register u16 numelected = 0;
	register u8  boxcount   = 0;
	u8 hit[BOXSZ];
	
	for (boxcount = 0; boxcount < 42; boxcount += 2)
	{
		zeroarray(hit, BOXSZ);	// Zero out array
		// Create sbox from equation
		while(numelected < BOXSZ)
		{
			register float potent = ( (0.5 * u * ( sin(   ((g * x) / 256.0) + v   ) )) +
					          (0.5 * v * ( sin(   ((u * x) / 256.0) + g   ) )) +
						  (0.5 * g * ( sin(   ((v * x) / 256.0) + u   ) )) + 384 ) / 3.0;
		
			
			u16 candidate = (u16)(ceil(potent));
			if (candidate >= BOXSZ)
				goto keepgoing;
			if (!(*(hit + candidate)))
			{
				print_space_format256(candidate, 0);
				PRINTN(numelected);
				*(hit + candidate) = 1;
				
				// Set substitution value within sbox
				*(sboxarray + (boxcount * BOXSZ) + i) = candidate;

				// Set corresponding inverse substitution value within corresponding inverse sbox
				*(sboxarray + ((boxcount + 1) * BOXSZ) + candidate) = i;
				++i;
				++numelected;
			}
			keepgoing:
				++x;
		}
		exit(0);
	}
}

static inline void triangle()
{
	register u64 all    = G;
	register u64 good   = S;
	register u64 things = H;
	
	H = good   ^  things;
	S  = all    ^  good;
	G  = things ^  all;
}

static inline void minitriangle(u64* x, u64* y, u64* z)
{
	register u64 regx = *x;
	register u64 regy = *y;
	register u64 regz = *z;
	
	*x = regx ^ regy;
	*y = regy ^ regz;
	*z = regz ^ regx;
}

static inline void sow(u64* x) // decree is actually a 'u8' type
{
	register u64 faith = 0x0000000000000000 | ((u64)(order) << 48);	// Places decree value into 6th byte
	
	switch(order % BLKBLKSZ)
	{
		case 0 : ;
			 faith = GETBYTE0_ASBYTE4(S) |
			 	 GETBYTE4_ASBYTE1(S) |
			 	 GETBYTE1_ASBYTE5(S) |
			 	 GETBYTE5_ASBYTE2(S) |
			 	 GETBYTE2_ASBYTE6(S) |
			 	 GETBYTE6_ASBYTE3(S) ^
			 	 GETBYTE3_ASBYTE0(S);
			 break;
		case 1 : ;
			 faith = GETBYTE0(S) |
			 	 GETBYTE1(S) |
			 	 GETBYTE2(S) |
			 	 GETBYTE3(S) |
			 	 GETBYTE4(S) |
			 	 GETBYTE5(S) ^
			 	 GETBYTE6(S);
			 break;
		case 2 : ;
			 faith = GETBYTE0_ASBYTE5(S) |
			 	 GETBYTE5_ASBYTE3(S) |
			 	 GETBYTE3_ASBYTE1(S) |
			 	 GETBYTE1_ASBYTE6(S) |
			 	 GETBYTE6_ASBYTE4(S) |
			 	 GETBYTE4_ASBYTE2(S) ^
			 	 GETBYTE2_ASBYTE0(S);
			 break;
		case 3 : ;
			 faith = GETBYTE0_ASBYTE2(S) |
			 	 GETBYTE2_ASBYTE4(S) |
			 	 GETBYTE4_ASBYTE6(S) |
			 	 GETBYTE6_ASBYTE1(S) |
			 	 GETBYTE1_ASBYTE3(S) |
			 	 GETBYTE3_ASBYTE5(S) ^
			 	 GETBYTE5_ASBYTE0(S);
			 break;
		case 4 : ;
			 faith = GETBYTE0_ASBYTE6(S) |
			 	 GETBYTE6_ASBYTE5(S) |
			 	 GETBYTE5_ASBYTE4(S) |
			 	 GETBYTE4_ASBYTE3(S) |
			 	 GETBYTE3_ASBYTE2(S) |
			 	 GETBYTE2_ASBYTE1(S) ^
			 	 GETBYTE1_ASBYTE0(S);
			 break;
		case 5 : ;
			 faith = GETBYTE0_ASBYTE6(S) |
			 	 GETBYTE6_ASBYTE5(S) |
			 	 GETBYTE5_ASBYTE4(S) |
			 	 GETBYTE4_ASBYTE3(S) |
			 	 GETBYTE3_ASBYTE2(S) |
			 	 GETBYTE2_ASBYTE1(S) ^
			 	 GETBYTE1_ASBYTE0(S);
			 break;
		case 6 : ;
			 faith = GETBYTE0_ASBYTE3(S) |
			 	 GETBYTE3_ASBYTE6(S) |
			 	 GETBYTE6_ASBYTE2(S) |
			 	 GETBYTE2_ASBYTE5(S) |
			 	 GETBYTE5_ASBYTE1(S) |
			 	 GETBYTE1_ASBYTE4(S) ^
			 	 GETBYTE4_ASBYTE0(S);
	}
	*x ^= faith;
}

static inline void keypathways(u8* sbox, u8* key)
{
	*(key     ) = DYNAMICBOX(sbox, *(key     ));
	*(key +  1) = DYNAMICBOX(sbox, *(key +  1));
	*(key +  2) = DYNAMICBOX(sbox, *(key +  2));
	*(key +  3) = DYNAMICBOX(sbox, *(key +  3));
	*(key +  4) = DYNAMICBOX(sbox, *(key +  4));
	*(key +  5) = DYNAMICBOX(sbox, *(key +  5));
	*(key +  6) = DYNAMICBOX(sbox, *(key +  6));
	*(key +  7) = DYNAMICBOX(sbox, *(key +  7));
	*(key +  8) = DYNAMICBOX(sbox, *(key +  8));
	*(key +  9) = DYNAMICBOX(sbox, *(key +  9));
	*(key + 10) = DYNAMICBOX(sbox, *(key + 10));
	*(key + 11) = DYNAMICBOX(sbox, *(key + 11));
	*(key + 12) = DYNAMICBOX(sbox, *(key + 12));
	*(key + 13) = DYNAMICBOX(sbox, *(key + 13));
	*(key + 14) = DYNAMICBOX(sbox, *(key + 14));
	*(key + 15) = DYNAMICBOX(sbox, *(key + 15));
	*(key + 16) = DYNAMICBOX(sbox, *(key + 16));
	*(key + 17) = DYNAMICBOX(sbox, *(key + 17));
	*(key + 18) = DYNAMICBOX(sbox, *(key + 18));
	*(key + 19) = DYNAMICBOX(sbox, *(key + 19));
	*(key + 20) = DYNAMICBOX(sbox, *(key + 20));
}

static inline void datapathways(u8* sbox)
{
	*(F_i_E_L_D     ) = DYNAMICBOX(sbox, *(F_i_E_L_D     ));
	*(F_i_E_L_D +  1) = DYNAMICBOX(sbox, *(F_i_E_L_D +  1));
	*(F_i_E_L_D +  2) = DYNAMICBOX(sbox, *(F_i_E_L_D +  2));
	*(F_i_E_L_D +  3) = DYNAMICBOX(sbox, *(F_i_E_L_D +  3));
	*(F_i_E_L_D +  4) = DYNAMICBOX(sbox, *(F_i_E_L_D +  4));
	*(F_i_E_L_D +  5) = DYNAMICBOX(sbox, *(F_i_E_L_D +  5));
	*(F_i_E_L_D +  6) = DYNAMICBOX(sbox, *(F_i_E_L_D +  6));
	*(F_i_E_L_D +  7) = DYNAMICBOX(sbox, *(F_i_E_L_D +  7));
	*(F_i_E_L_D +  8) = DYNAMICBOX(sbox, *(F_i_E_L_D +  8));
	*(F_i_E_L_D +  9) = DYNAMICBOX(sbox, *(F_i_E_L_D +  9));
	*(F_i_E_L_D + 10) = DYNAMICBOX(sbox, *(F_i_E_L_D + 10));
	*(F_i_E_L_D + 11) = DYNAMICBOX(sbox, *(F_i_E_L_D + 11));
	*(F_i_E_L_D + 12) = DYNAMICBOX(sbox, *(F_i_E_L_D + 12));
	*(F_i_E_L_D + 13) = DYNAMICBOX(sbox, *(F_i_E_L_D + 13));
	*(F_i_E_L_D + 14) = DYNAMICBOX(sbox, *(F_i_E_L_D + 14));
	*(F_i_E_L_D + 15) = DYNAMICBOX(sbox, *(F_i_E_L_D + 15));
	*(F_i_E_L_D + 16) = DYNAMICBOX(sbox, *(F_i_E_L_D + 16));
	*(F_i_E_L_D + 17) = DYNAMICBOX(sbox, *(F_i_E_L_D + 17));
	*(F_i_E_L_D + 18) = DYNAMICBOX(sbox, *(F_i_E_L_D + 18));
	*(F_i_E_L_D + 19) = DYNAMICBOX(sbox, *(F_i_E_L_D + 19));
	*(F_i_E_L_D + 20) = DYNAMICBOX(sbox, *(F_i_E_L_D + 20));
	*(F_i_E_L_D + 21) = DYNAMICBOX(sbox, *(F_i_E_L_D + 21));
	*(F_i_E_L_D + 22) = DYNAMICBOX(sbox, *(F_i_E_L_D + 22));
	*(F_i_E_L_D + 23) = DYNAMICBOX(sbox, *(F_i_E_L_D + 23));
	*(F_i_E_L_D + 24) = DYNAMICBOX(sbox, *(F_i_E_L_D + 24));
	*(F_i_E_L_D + 25) = DYNAMICBOX(sbox, *(F_i_E_L_D + 25));
	*(F_i_E_L_D + 26) = DYNAMICBOX(sbox, *(F_i_E_L_D + 26));
	*(F_i_E_L_D + 27) = DYNAMICBOX(sbox, *(F_i_E_L_D + 27));
	*(F_i_E_L_D + 28) = DYNAMICBOX(sbox, *(F_i_E_L_D + 28));
	*(F_i_E_L_D + 29) = DYNAMICBOX(sbox, *(F_i_E_L_D + 29));
	*(F_i_E_L_D + 30) = DYNAMICBOX(sbox, *(F_i_E_L_D + 30));
	*(F_i_E_L_D + 31) = DYNAMICBOX(sbox, *(F_i_E_L_D + 31));
	*(F_i_E_L_D + 32) = DYNAMICBOX(sbox, *(F_i_E_L_D + 32));
	*(F_i_E_L_D + 33) = DYNAMICBOX(sbox, *(F_i_E_L_D + 33));
	*(F_i_E_L_D + 34) = DYNAMICBOX(sbox, *(F_i_E_L_D + 34));
	*(F_i_E_L_D + 35) = DYNAMICBOX(sbox, *(F_i_E_L_D + 35));
	*(F_i_E_L_D + 36) = DYNAMICBOX(sbox, *(F_i_E_L_D + 36));
	*(F_i_E_L_D + 37) = DYNAMICBOX(sbox, *(F_i_E_L_D + 37));
	*(F_i_E_L_D + 38) = DYNAMICBOX(sbox, *(F_i_E_L_D + 38));
	*(F_i_E_L_D + 39) = DYNAMICBOX(sbox, *(F_i_E_L_D + 39));
	*(F_i_E_L_D + 40) = DYNAMICBOX(sbox, *(F_i_E_L_D + 40));
	*(F_i_E_L_D + 41) = DYNAMICBOX(sbox, *(F_i_E_L_D + 41));
	*(F_i_E_L_D + 42) = DYNAMICBOX(sbox, *(F_i_E_L_D + 42));
	*(F_i_E_L_D + 43) = DYNAMICBOX(sbox, *(F_i_E_L_D + 43));
	*(F_i_E_L_D + 44) = DYNAMICBOX(sbox, *(F_i_E_L_D + 44));
	*(F_i_E_L_D + 45) = DYNAMICBOX(sbox, *(F_i_E_L_D + 45));
	*(F_i_E_L_D + 46) = DYNAMICBOX(sbox, *(F_i_E_L_D + 46));
	*(F_i_E_L_D + 47) = DYNAMICBOX(sbox, *(F_i_E_L_D + 47));
	*(F_i_E_L_D + 48) = DYNAMICBOX(sbox, *(F_i_E_L_D + 48));
}

static inline void weave()
{
	// 0 3 6 2 5 1 4
	// 4 1 5 2 6 3 0
	u64* ptr0 = (u64*)(F_i_E_L_D);
	u64* ptr1 = (u64*)(F_i_E_L_D + (BLKBLKSZ));
	u64* ptr2 = (u64*)(F_i_E_L_D + (BLKBLKSZ * 2));
	u64* ptr3 = (u64*)(F_i_E_L_D + (BLKBLKSZ * 3));
	u64* ptr4 = (u64*)(F_i_E_L_D + (BLKBLKSZ * 4));
	u64* ptr5 = (u64*)(F_i_E_L_D + (BLKBLKSZ * 5));
	u64* ptr6 = (u64*)(F_i_E_L_D + (BLKBLKSZ * 6));
	
	register u64 area6 = *ptr6;	
	register u64 area5 = *ptr5;
	register u64 area4 = *ptr4;
	register u64 area3 = *ptr3;
	register u64 area2 = *ptr2;
	register u64 area1 = *ptr1;
	register u64 area0 = *ptr0;
	
	*ptr3 = area0 ^ area2 ^ area5;				// 0 -> 3
	*ptr4 = ROTATE3BYTESOF7_LEFT(area1 ^ area3 ^ area6);	// 1 -> 4
	*ptr5 = ROTATE6BYTESOF7_LEFT(area2 ^ area4 ^ area0);	// 2 -> 5
	*ptr6 = ROTATE2BYTESOF7_LEFT(area3 ^ area5 ^ area1);	// 3 -> 6
	*ptr0 = ROTATE5BYTESOF7_LEFT(area4 ^ area6 ^ area2);	// 4 -> 0
	*ptr1 = ROTATE1BYTEOF7_LEFT(area5 ^ area0 ^ area3);	// 5 -> 1
	*ptr2 = ROTATE4BYTESOF7_LEFT(CLEARBYTE7(area6 ^ area1 ^ area4) | *(F_i_E_L_D + MSGBLKSZ - 1)); // 6 -> 2
	
}

static inline void unweave()
{
	u64* ptr4 = (u64*)(F_i_E_L_D);			// 0 -> 4
	u64* ptr5 = (u64*)(F_i_E_L_D + (BLKBLKSZ));	// 1 -> 5
	u64* ptr6 = (u64*)(F_i_E_L_D + (BLKBLKSZ * 2)); // 2 -> 6
	u64* ptr0 = (u64*)(F_i_E_L_D + (BLKBLKSZ * 3)); // 3 -> 0
	u64* ptr1 = (u64*)(F_i_E_L_D + (BLKBLKSZ * 4)); // 4 -> 1
	u64* ptr2 = (u64*)(F_i_E_L_D + (BLKBLKSZ * 5)); // 5 -> 2
	u64* ptr3 = (u64*)(F_i_E_L_D + (BLKBLKSZ * 6)); // 6 -> 3
	
	register u64 area6 = *ptr6;	
	register u64 area5 = *ptr5;
	register u64 area4 = *ptr4;
	register u64 area3 = *ptr3;
	register u64 area2 = *ptr2;
	register u64 area1 = *ptr1;
	register u64 area0 = *ptr0;
	
	area1 = ROTATE3BYTESOF7_RIGHT(area1);
	area2 = ROTATE6BYTESOF7_RIGHT(area2);
	area3 = ROTATE2BYTESOF7_RIGHT(area3);
	area4 = ROTATE5BYTESOF7_RIGHT(area4);
	area5 = ROTATE1BYTEOF7_RIGHT(area5);
	area6 = ROTATE4BYTESOF7_RIGHT(area6);
	
	*ptr5 = area0 ^ area5 ^ area3 ^ area6 ^ area4;
	*ptr6 = area1 ^ area3 ^ *ptr5;
	*ptr4 = area0 ^ area2 ^ *ptr5;
	*ptr2 = area4 ^ *ptr4 ^ *ptr6;
	*ptr0 = area0 ^ *ptr2 ^ *ptr5;
	*ptr3 = area5 ^ *ptr0 ^ *ptr5;
	*ptr1 = CLEARBYTE7(area1 ^ *ptr3 ^ *ptr6) | *(F_i_E_L_D + MSGBLKSZ - 1);
}
	
static inline void clockwise(u8* box, u8* prevkey, u8* nxtkey)
{
	u8 holdorder = order;
	keytoreg(prevkey);
	minitriangle(&hG, &hS, &hH);
	regtokey(nxtkey);
	switchlock12(box, (nxtkey)    , (nxtkey + 1));
	switchlock12(box, (nxtkey + 1), (nxtkey + 2));
	switchlock12(box, (nxtkey + 2), (nxtkey + 3));
	switchlock12(box, (nxtkey + 3), (nxtkey + 4));
	switchlock12(box, (nxtkey + 4), (nxtkey + 5));
	switchlock12(box, (nxtkey + 5), (nxtkey + 6));
	keypathways(box, nxtkey);
	order = holdorder;
}

static inline void keygen()
{
	clockwise(sboxarray,                lineup, 	           lineup + (KEYSZ));
	clockwise(sboxarray + (BOXSZ *  2), lineup + (KEYSZ),      lineup + (KEYSZ *  2));
	clockwise(sboxarray + (BOXSZ *  4), lineup + (KEYSZ *  2), lineup + (KEYSZ *  3));
	clockwise(sboxarray + (BOXSZ *  6), lineup + (KEYSZ *  3), lineup + (KEYSZ *  4));
	clockwise(sboxarray + (BOXSZ *  8), lineup + (KEYSZ *  4), lineup + (KEYSZ *  5));
	clockwise(sboxarray + (BOXSZ * 10), lineup + (KEYSZ *  5), lineup + (KEYSZ *  6));
	clockwise(sboxarray + (BOXSZ * 12), lineup + (KEYSZ *  6), lineup + (KEYSZ *  7));
	clockwise(sboxarray + (BOXSZ * 14), lineup + (KEYSZ *  7), lineup + (KEYSZ *  8));
	clockwise(sboxarray + (BOXSZ * 16), lineup + (KEYSZ *  8), lineup + (KEYSZ *  9));
	clockwise(sboxarray + (BOXSZ * 18), lineup + (KEYSZ *  9), lineup + (KEYSZ * 10));
	clockwise(sboxarray + (BOXSZ * 20), lineup + (KEYSZ * 10), lineup + (KEYSZ * 11));
	clockwise(sboxarray + (BOXSZ * 22), lineup + (KEYSZ * 11), lineup + (KEYSZ * 12));
	clockwise(sboxarray + (BOXSZ * 24), lineup + (KEYSZ * 12), lineup + (KEYSZ * 13));
	clockwise(sboxarray + (BOXSZ * 26), lineup + (KEYSZ * 13), lineup + (KEYSZ * 14));
	clockwise(sboxarray + (BOXSZ * 28), lineup + (KEYSZ * 14), lineup + (KEYSZ * 15));
	clockwise(sboxarray + (BOXSZ * 30), lineup + (KEYSZ * 15), lineup + (KEYSZ * 16));
	clockwise(sboxarray + (BOXSZ * 32), lineup + (KEYSZ * 16), lineup + (KEYSZ * 17));
	clockwise(sboxarray + (BOXSZ * 34), lineup + (KEYSZ * 17), lineup + (KEYSZ * 18));
	clockwise(sboxarray + (BOXSZ * 36), lineup + (KEYSZ * 18), lineup + (KEYSZ * 19));
	clockwise(sboxarray + (BOXSZ * 38), lineup + (KEYSZ * 19), lineup + (KEYSZ * 20));
}

void invisible(u8* box)
{
	datapathways(box);
}

void visible(u8* box)
{
	datapathways(box);
}

static inline void setup(u8* field, u8* key)
{
	if (!F_i_E_L_D)
	{
		F_i_E_L_D = field;
		nbytesto(lineup, key, KEYSZ);
		setkey(key);
		boxgen(G);
		keygen();
	}
}

void encrypt(char* field, char* key)
{
	//setup((u8*)(field), (u8*)(key));
	
	//invisible();
	//clockwise(*(sboxarray));
	// ...
}



#endif // _CRYPT_
