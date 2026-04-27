import Navbar from "@/components/Navbar"
import Footer from "@/components/Footer"

export default function Main(){
  return (
    <>
      <Navbar/>
      <div className="flex flex-col">
        <div className="h-auto w-full bg-primary pl-[10%] pr-[10%] pt-10 pb-10">
          <h1 className="text-[3.5rem] text-background m-0">ApolOS</h1>
          <h2 className="text-xl text-background font-bold">Nasa&apos;s OS))</h2>
          <p className="text-[1rem] text-background">Lorem ipsum dolor sit amet consectetur adipisicing elit. Nulla harum accusamus hic eaque, architecto, optio perferendis blanditiis, quis quibusdam doloribus minus ea veniam. Illum eius temporibus cumque doloribus obcaecati beatae!</p>
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