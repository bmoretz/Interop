using System;
using System.Runtime.InteropServices;

namespace Invoke_CSharp
{
    class dll_invoker
    {
        #region External Function Prototypes

        [DllImport( "Generator.dll", CallingConvention = CallingConvention.StdCall )]
        static extern Guid Empty();

        [DllImport( "Generator.dll", CallingConvention = CallingConvention.StdCall )]
        static extern Guid Generate();

        [DllImport( "Generator.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode )]
        static extern Guid FromStringW( string idString );

        [DllImport( "Generator.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi )]
        static extern Guid FromStringA( string idString );

        #endregion

        #region Definitions

        const string GuidStringToConvert = "{FADDEC2A-B4C1-47A4-8065-14C038E4AD67}";
        const int GuidsToDisplay = 100;

        #endregion

        #region Entry Point

        /// <summary>
        /// Application Entry Point
        /// </summary>
        static void Main( string[] args )
        {
            DisplayEmptyGuid();

            for ( int index = 0; index < GuidsToDisplay; index++ )
            {
                DisplayNewGuid();
            }

            DisplayParsedWideGuid();
            DisplayParsedAsciiGuid();

            Console.ReadKey();
        }

        #endregion

        #region Internal

        static void DisplayNewGuid()
        {
            Console.WriteLine
            (
                Generate().ToString()
            );
        }

        static void DisplayEmptyGuid()
        {
            Console.WriteLine
            (
                Empty().ToString()
            );
        }

        static void DisplayParsedWideGuid()
        {
            Console.WriteLine
            (
                FromStringW
                (
                    GuidStringToConvert
                ).ToString()
            );
        }

        static void DisplayParsedAsciiGuid()
        {
            Console.WriteLine
            (
                FromStringA
                (
                    GuidStringToConvert
                ).ToString()
            );
        }

        #endregion
    }
}