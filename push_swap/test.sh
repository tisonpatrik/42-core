#!/bin/bash

# Test script for push_swap checker
# Tests if the checker correctly validates a sequence of operations

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}Testing push_swap checker...${NC}"

# Check if checker binary exists
if [ ! -f "./bin/checker" ]; then
    echo -e "${RED}Error: checker binary not found. Please run 'make bonus' first.${NC}"
    exit 1
fi

# Run the test command
echo "Running test: echo \"rra\npb\nsa\nrra\npa\" | ./bin/checker 3 2 1 0"
result=$(echo -e "rra\npb\nsa\nrra\npa" | ./bin/checker 3 2 1 0)

# Check the result
if [ "$result" = "OK" ]; then
    echo -e "${GREEN}✓ Test 1 PASSED: Checker returned 'OK' as expected${NC}"
else
    echo -e "${RED}✗ Test 1 FAILED: Checker returned '$result' instead of 'OK'${NC}"
    echo -e "${RED}This indicates there's an error in the checker code.${NC}"
    exit 1
fi

echo ""

# Test 2: Invalid operation sequence (should return KO)
echo "Running test 2: echo \"sa\nrra\npb\" | ./bin/checker 3 2 1 0"
result2=$(echo -e "sa\nrra\npb" | ./bin/checker 3 2 1 0)

# Check the result
if [ "$result2" = "KO" ]; then
    echo -e "${GREEN}✓ Test 2 PASSED: Checker returned 'KO' as expected${NC}"
else
    echo -e "${RED}✗ Test 2 FAILED: Checker returned '$result2' instead of 'KO'${NC}"
    echo -e "${RED}This indicates there's an error in the checker code.${NC}"
    exit 1
fi

echo ""

# Test 3: Invalid input (non-numeric argument - should return Error)
echo "Running test 3: echo \"\" | ./bin/checker 3 2 one 0"
result3=$(echo "" | ./bin/checker 3 2 one 0 2>&1)

# Check the result
if [ "$result3" = "Error" ]; then
    echo -e "${GREEN}✓ Test 3 PASSED: Checker returned 'Error' as expected${NC}"
else
    echo -e "${RED}✗ Test 3 FAILED: Checker returned '$result3' instead of 'Error'${NC}"
    echo -e "${RED}This indicates there's an error in the checker code.${NC}"
    exit 1
fi

echo ""

# Test 4: Empty string argument (should return Error)
echo "Running test 4: echo \"\" | ./bin/checker \"\" 1"
result4=$(echo "" | ./bin/checker "" 1 2>&1)

# Check the result
if [ "$result4" = "Error" ]; then
    echo -e "${GREEN}✓ Test 4 PASSED: Checker returned 'Error' as expected${NC}"
else
    echo -e "${RED}✗ Test 4 FAILED: Checker returned '$result4' instead of 'Error'${NC}"
    echo -e "${RED}This indicates there's an error in the checker code.${NC}"
    exit 1
fi

echo ""

# Test 5: Large array test (push_swap + checker integration)
echo "Running test 5: Large array integration test"
ARG="213 189 368 202 23 72 26 124 432 425 12 138 347 71 9 41 435 301 272 475 193 355 467 172 380 190 445 267 473 484 100 5 318 94 52 219 476 351 214 31 39 381 477 242 139 434 498 396 1 97 403 283 21 208 127 228 185 271 474 57 451 384 47 217 379 479 64 95 265 431 412 163 125 446 234 145 442 285 235 393 82 449 156 10 75 256 108 334 88 280 464 167 50 184 382 330 453 395 135 341 87 137 493 150 118 466 471 422 472 122 407 385 400 415 261 421 68 164 7 378 201 433 344 315 377 245 460 441 231 367 427 282 183 239 480 289 440 302 470 332 426 313 408 146 186 191 179 303 105 324 399 86 490 180 402 58 294 300 424 448 19 34 130 101 178 226 80 160 264 397 273 173 372 365 106 206 266 410 6 373 28 247 401 360 255 11 491 121 352 284 187 141 416 20 119 209 62 394 238 61 227 494 126 147 450 134 174 374 298 481 200 73 240 136 33 257 224 114 250 117 364 143 205 487 216 338 468 181 151 314 243 419 2 296 24 293 336 457 323 262 111 93 197 43 376 157 195 496 17 60 258 148 96 166 15 3 375 305 370 317 349 78 176 104 295 22 292 316 194 128 192 153 260 98 391 0 53 439 69 277 144 188 270 486 482 199 444 342 154 32 159 251 177 253 44 91 309 45 353 83 438 495 175 116 359 4 321 259 369 54 67 218 142 131 229 40 168 463 230 182 49 74 233 497 55 361 358 350 103 279 36 171 492 81 90 123 155 455 339 437 362 196 414 133 113 311 275 30 458 290 140 92 462 337 18 268 485 452 288 109 276 363 371 162 348 169 366 110 392 220 386 158 326 307 112 215 225 443 51 281 286 454 406 354 356 42 291 312 430 46 329 35 488 489 436 429 409 248 70 65 420 99 236 79 232 413 210 418 25 306 297 423 102 132 207 129 14 8 165 263 465 237 223 483 254 328 269 120 66 84 77 461 63 37 278 198 221 404 308 161 274 299 249 211 343 152 203 428 459 115 499 320 252 388 319 38 478 417 56 85 241 310 149 405 107 76 456 27 287 327 331 222 212 325 346 59 13 387 469 335 16 390 170 447 304 246 340 411 389 29 48 345 204 333 383 398 357 89 322 244"
result5=$(./bin/push_swap $ARG | ./bin/checker $ARG)

# Check the result
if [ "$result5" = "OK" ]; then
    echo -e "${GREEN}✓ Test 5 PASSED: Large array integration test returned 'OK' as expected${NC}"
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}✗ Test 5 FAILED: Large array integration test returned '$result5' instead of 'OK'${NC}"
    echo -e "${RED}This indicates there's an error in the push_swap or checker code.${NC}"
    exit 1
fi
