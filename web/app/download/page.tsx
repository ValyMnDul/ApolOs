import Link from "next/link";

export default function Download(){
    return (
        <main className="p-6 max-w-4xl mx-auto">
            <nav className="mb-12 border-b border-[#222] pb-4">
                <Link
                href="/"
                className="text-[10px] hover:text-white uppercase tracking-widest underline decoration-[#444]"
                >
                RET_TO_HOME
                </Link>
            </nav>

            <div className="max-w-3xl mx-auto border border-[#222] p-6 bg-[#050505]">
                <header className="mb-10">
                    <h1 className="text-white text-lg font-bold uppercase tracking-tighter mb-1">
                        Binary Distribution
                    </h1>

                    <p className="text-[10px] text-[#555] uppercase">
                        Architecture: x86_32 | Format: Flat Binary | Target:
                        i386-compatible
                    </p>
                </header>

                <section className="mb-12">
                <div className="bg-[#111] border border-[#222] p-8 text-center">
                    <p className="text-xs mb-6 text-gray-400 uppercase tracking-widest">
                    Ready for hardware or emulation
                    </p>

                    <a
                    href="/apolos.bin"
                    download="apolos.bin"
                    className="inline-block bg-[#eeeeee] text-black px-10 py-3 text-xs font-bold hover:bg-white transition-none uppercase tracking-tighter"
                    >
                    Get apolos.bin
                    </a>
                </div>
                </section>

                <section className="mb-12">
                    <h2 className="text-white text-xs font-bold uppercase mb-4 border-l-2 border-white pl-2">
                        Quick_Start (Ubuntu / Debian)
                    </h2>

                    <p className="text-xs mb-4 leading-relaxed">
                        The following command updates repositories, installs the QEMU
                        emulator, and executes the ApolOS binary in a raw drive
                        environment:
                    </p>

                    <div className="bg-black border border-[#333] p-4 font-mono text-[11px] relative">
                        <code className="text-[#00ff41] leading-relaxed break-all">
                        sudo apt update && sudo apt install -y qemu-system-x86 &&
                        qemu-system-i386 -drive format=raw,file=apolos.bin
                        </code>
                    </div>
                </section>
                
                <footer className="grid grid-cols-2 gap-4 border-t border-[#222] pt-6 mt-8">
                    <div>
                        <span className="block text-[10px] text-[#555] uppercase font-bold">
                        Memory_Entry
                        </span>

                        <span className="text-xs font-mono">
                        0x00007C00 (MBR)
                        </span>
                    </div>

                    <div>
                        <span className="block text-[10px] text-[#555] uppercase font-bold">
                        Kernel_Base
                        </span>

                        <span className="text-xs font-mono">0x00001000</span>
                    </div>

                    <div>
                        <span className="block text-[10px] text-[#555] uppercase font-bold">
                        File_Size
                        </span>

                        <span className="text-xs font-mono">
                        ~31 KB (60 Sectors)
                        </span>gdggdkhhgds
                    </div>
                </footer>
            </div>
        </main>
    )
}