// Welcome to the TypeScript Playground, this is a website
// which gives you a chance to write, share and learn TypeScript.

// You could think of it in three ways:
//
//  - A location to learn TypeScript where nothing can break
//  - A place to experiment with TypeScript syntax, and share the URLs with others
//  - A sandbox to experiment with different compiler features of TypeScript

const data = 0b100011101011;
const crc = 0b101001;
const dataBitLength = Number(data).toString(2).length;
const crcBitLength = Number(crc).toString(2).length;

let arr = [];
let current = data >> (12 - crcBitLength);

// console.log(Number(first & (1 << 5)).toString(2));

if (current & (1 << (crcBitLength - 1))) {
    arr.push(1);
    current ^= crc;
} else {
    arr.push(0);
    current ^= 0;
}
// current = data & (current << 6) ;
console.log("data", Number(data ).toString(2));
console.log("current", Number(((current << 6) | data) & ~(1 << 11) ).toString(2));
console.log(arr);
// console.log(dataBitLength)
