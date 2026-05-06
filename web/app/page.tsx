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
        
      </div>
    </main>
  )
}