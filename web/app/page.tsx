import Image from "next/image"

import Navbar from "@/components/Navbar"
import Footer from "@/components/Footer"

export default function Main(){
  return (
    <>
      <Navbar/>
      <div className="flex flex-col">
        <div className="flex flex-col md:flex-row justify-between items-center gap-8">
          <div className="w-full md:w-[60%]">
            <h1 className="text-[3.5rem] text-background m-0">ApolOS</h1>
            <h2 className="text-xl text-background font-bold">Nasa&apos;s OS</h2>
            <p className="text-lg text-background/90 max-w-xl leading-relaxed">Lorem ipsum dolor sit amet consectetur adipisicing elit. Nulla harum accusamus hic eaque, architecto, optio perferendis blanditiis, quis quibusdam doloribus minus ea veniam. Illum eius temporibus cumque doloribus obcaecati beatae!</p>
          </div>
          <div className="w-full md:w-[35%]">
            <Image 
              src="/test.png" 
              width={300} 
              height={300} 
              alt="ApolOS Interface"
              priority
              className="w-full h-auto object-contain" 
            />
          </div>
        </div>
        <div className="w-full h-auto pl-[10%] pr-[10%] pt-10 pb-10">
          <section>
            FIRST SECTION
          </section>
        </div>
      </div>
      <Footer/>
    </>
  )

}