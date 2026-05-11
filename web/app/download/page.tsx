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

            </div>
        </main>
    )
}