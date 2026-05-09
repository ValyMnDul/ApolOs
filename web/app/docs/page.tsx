import Link from "next/link"

export default function Docs(){
    return (
        <main className="p-6 max-w-4xl mx-auto">
            <Link href="/" className="text-xs text-gray-500 hover:text-white mb-8 block font-bold tracking-tighter underline">RET_TO_HOME</Link>

            <h2 className="text-xl text-white font-bold mb-10 tracking-tighter border-l-4 border-white pl-4 uppercase">
                Documentation
            </h2>

            <div className="space-y-12">
                <section>
                    <h3 className="text-xs font-bold mb-4 text-gray-500 uppercase">01. GDT_Layout</h3>
                    <p className="text-sm mb-4">The GDT descriptor defines the code and data segments required for Protected Mode.</p>
                    <div className="overflow-x-auto">
                        <table className="w-full text-[10px] text-left border-collapse">
                            <thead>
                                <tr className="border-b border-gray-800">
                                    <th className="p-2 text-gray-500 uppercase">Segment</th>
                                    <th className="p-2 text-gray-500 uppercase">Base</th>
                                    <th className="p-2 text-gray-500 uppercase">Limit</th>
                                    <th className="p-2 text-gray-500 uppercase">Access</th>
                                </tr>
                            </thead>
                        </table>
                    </div>
                </section>
            </div>
        </main>
    )
}