# crc-typescript
https://github.com/includeos/vmbuild/blob/master/src/crc32.cpp
- https://dl.acm.org/doi/pdf/10.1145/63030.63037
- https://medium.com/@vbabak/implementing-crc32-in-typescript-ff3453a1a9e7

```typescript
class CRC {
    private polynomial: number;
    private initialValue: number;
    private finalXorValue: number;
    private inputReflected: boolean;
    private outputReflected: boolean;
    private width: number;

    constructor(
        polynomial: number,
        initialValue: number,
        finalXorValue: number,
        inputReflected: boolean,
        outputReflected: boolean,
        width: number
    ) {
        this.polynomial = polynomial;
        this.initialValue = initialValue;
        this.finalXorValue = finalXorValue;
        this.inputReflected = inputReflected;
        this.outputReflected = outputReflected;
        this.width = width;
    }

    private reflect(value: number, width: number): number {
        let result = 0;
        for (let i = 0; i < width; i++) {
            if (value & (1 << i)) {
                result |= (1 << (width - 1 - i));
            }
        }
        return result;
    }

    public compute(data: Buffer): number {
        let crc = this.initialValue;

        for (let byte of data) {
            let inputByte = this.inputReflected ? this.reflect(byte, 8) : byte;
            crc ^= inputByte << (this.width - 8);

            for (let i = 0; i < 8; i++) {
                const msb = (crc & (1 << (this.width - 1))) !== 0;
                crc <<= 1;
                if (msb) {
                    crc ^= this.polynomial;
                }
            }
        }

        if (this.outputReflected) {
            crc = this.reflect(crc, this.width);
        }

        return crc ^ this.finalXorValue;
    }
}

// Example usage:
const crc32 = new CRC(
    0xEDB88320, // Polynomial for CRC-32
    0xFFFFFFFF, // Initial value
    0xFFFFFFFF, // Final XOR value
    false,      // Input not reflected
    false,      // Output not reflected
    32          // Width
);

const data = Buffer.from("Hello, world!");
const crcValue = crc32.compute(data);
console.log(`CRC-32: ${crcValue.toString(16).toUpperCase()}`);
```

```typescript
class CRC32 {
    private table: number[];

    constructor() {
        this.table = this.generateTable();
    }

    private generateTable(): number[] {
        const table = new Array(256);
        const polynomial = 0xEDB88320;

        for (let i = 0; i < 256; i++) {
            let crc = i;
            for (let j = 8; j > 0; j--) {
                crc = (crc & 1) ? (crc >>> 1) ^ polynomial : (crc >>> 1);
            }
            table[i] = crc >>> 0; // Ensure unsigned
        }
        return table;
    }

    public compute(data: Buffer): number {
        let crc = 0xFFFFFFFF;

        for (let byte of data) {
            const index = (crc ^ byte) & 0xFF;
            crc = (crc >>> 8) ^ this.table[index];
        }

        return crc ^ 0xFFFFFFFF; // Final XOR
    }
}

// Example usage
const crc32 = new CRC32();
const data = Buffer.from("Hello, world!");
const crcValue = crc32.compute(data);
console.log(`CRC-32: ${crcValue.toString(16).toUpperCase()}`);
```
