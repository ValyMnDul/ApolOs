import Link from "next/link"

export default function Home(){
  return (
    <main className="p-6 max-w-4xl mx-auto">
      <header className="border-b border-gray-800 pb-4 mb-8 flex justify-between items-end">
        <div>
          <h1 className="text-2xl font-bold text-white uppercase tracking-tighter">ApolOS</h1>
          <p className="text-[10px] text-gray-500">TARGET: x86_32 | MODE: PROTECTED</p>
        </div>
        <nav className="flex gap-6 text-sm">
          <Link href="/docs" className="hover:text-white border-b border-gray-700">DOCS</Link>
          <Link href="/download" className="hover:text-white border-b border-gray-700">BIN</Link>
          <a href="#" className="hover:text-white border-b border-gray-700">SOURCE</a>
        </nav>
      </header>

      <section className="mb-12">
        <p className="text-base leading-relaxed mb-6">
          Lorem ipsum dolor sit amet consectetur adipisicing elit. Numquam exercitationem sapiente porro voluptatem atque esse debitis provident? Odit atque optio quod itaque repellat ad fugiat beatae obcaecati voluptates. Perferendis, mollitia.
        </p>
      </section>

      <div className="grid grid-cols-1 md:grid-cols-2 gap-4 mb-12">
        <div className="border border-gray-800 p-4 bg-zinc-950">
          <h3 className="text-white text-xs font-bold mb-4 uppercase tracking-widest">Map</h3>
          <ul className="text-[11px] space-y-1">
            <li className="flex justify-between"><span>0x00007C00</span> <span className="text-gray-500">Bootloader</span></li>
            <li className="flex justify-between"><span>0x00001000</span> <span className="text-gray-500">Kernel Load</span></li>
            <li className="flex justify-between"><span>0x00008000</span> <span className="text-gray-500">Stack 16-bit</span></li>
            <li className="flex justify-between"><span>0x00090000</span> <span className="text-gray-500">Stack 32-bit</span></li>
          </ul>
        </div>
        <div className="border border-gray-800 p-4 bg-zinc-950">
          <h3 className="text-white text-xs font-bold mb-4 uppercase tracking-widest">Hardware_Control</h3>
          <ul className="text-[11px] space-y-1">
            <li className="flex justify-between"><span>VGA_BUF</span> <span className="text-gray-500">0xb8000</span></li>
            <li className="flex justify-between"><span>KBD_PORT</span> <span className="text-gray-500">0x60</span></li>
            <li className="flex justify-between"><span>PIC_MASTER</span> <span className="text-gray-500">0x20</span></li>
            <li className="flex justify-between"><span>CMOS_REG</span> <span className="text-gray-500">0x70</span></li>
          </ul>
        </div>
      </div>

      <section className="bg-black border border-gray-800 p-4 font-mono">
        <div className="text-xs text-gray-600 mb-4 font-bold tracking-tighter uppercase border-b border-gray-900 pb-1">
          Live_Shell_Preview
        </div>
        <div className="text-green-600 text-sm leading-tight">
          <p>Welcome to ApolOS</p>
          <p>&gt; nasa info voyager 1</p>
          <p className="text-white mt-1">--- Mission Control: voyager 1 ---</p>
          <p className="text-white">Status: Active</p>
          <p className="text-white">Details: Deep space probe studying the outer Solar System</p>
          <p>&gt; <span className="inline-block w-2 h-4 bg-green-600 animate-pulse align-middle ml-1"></span></p>
        </div>
      </section>
    </main>
  )
}