import Link from "next/link";

export default function Download(){
    return (
        <main className="p-6 max-w-4xl mx-auto">
            <Link href="/" className="text-xs text-gray-500 hover:text-white mb-8 block font-bold tracking-tighter underline">BACK TO HOME</Link>

            <div className="mt-20 border border-gray-800 bg-zinc-950 p-8 flex flex-col items-center">
                <h2 className="text-white font-bold mb-2 tracking-tighter uppercase">Binary_Distribution</h2>
                
                <p className="text-[10px] text-gray-500 mb-8 uppercase tracking-widest text-center">
                    v0.1-STABLE | MD5: f3a1c...
                </p>

                <div className="w-full max-w-xs space-y-4">
                    <button className="w-full bg-white text-black py-2 font-bold text-xs hover:bg-gray-200 transition-colors">
                        GET APOLOS.ISO
                    </button>
                    <div className="text-[10px] text-gray-400 font-mono bg-black p-3 border border-gray-800 break-all">
                        $ nasm -f bin boot.asm -o boot.bin<br/>
                        $ i686-elf-gcc -ffreestanding -c kernel.c<br/>
                        $ ld -o kernel.bin -Ttext 0x1000 kernel.o --oformat binary
                    </div>
                </div>
            </div>
        </main>
    )
}