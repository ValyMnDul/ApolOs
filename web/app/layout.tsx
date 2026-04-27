import type { Metadata } from "next";
import "./globals.css";
import { Poppins } from 'next/font/google';

export const metadata: Metadata = {
  title: "ApolOS",
  description: "ApolOS Portal",
};
const poppins = Poppins({
  subsets: ['latin'],
  weight: ['400', '700'],
  variable: '--font-poppins',
});

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html
      lang="en"
      className={`h-full antialiased bg-background `+ poppins.variable}
    >
      <body className="min-h-full flex flex-col">{children}</body>
    </html>
  );
}
