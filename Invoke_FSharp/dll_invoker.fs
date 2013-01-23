#light

open System
open System.Runtime.InteropServices

module
    GuidLibrary = 
        [<DllImport( "Generator.dll", CallingConvention=CallingConvention.StdCall )>] extern Guid Empty()
        ;
        [<DllImport( "Generator.dll", CallingConvention = CallingConvention.StdCall )>] extern Guid Generate()
        ;
        [<DllImport( "Generator.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode )>] extern Guid FromStringW( string )
        ;
        [<DllImport( "Generator.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi )>] extern Guid FromStringA( string )

module
    Constants =
        [<Literal>]
        let GuidStringToConvert = "{FADDEC2A-B4C1-47A4-8065-14C038E4AD67}"

ignore [ Console.WriteLine( GuidLibrary.Empty() ) ]
ignore [ for i in 0 .. 99 -> Console.WriteLine( GuidLibrary.Generate() ) ]
ignore [ Console.WriteLine( GuidLibrary.FromStringW( Constants.GuidStringToConvert ) ) ]
ignore [ Console.WriteLine( GuidLibrary.FromStringA( Constants.GuidStringToConvert ) ) ]

ignore [ Console.ReadKey() ];