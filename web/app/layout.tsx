import "./globals.css";
import type { Metadata } from "next";

export const metadata: Metadata = {
  title: "ApolOS v0.1",
  description: "NASA OS",
};

export default function RootLayout({
  children,
}: {
  children: React.ReactNode;
}) {
  return (
    <html lang="en">
      <body className="bg-black text-gray-300 font-mono antialiased selection:bg-white selection:text-black">
        {children}
      </body>
    </html>
  );
}