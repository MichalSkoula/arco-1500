using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace DIY_game_uploader
{
    class Program
    {
        #if DEBUG
            public static bool debug = true;
        #else
            public static bool debug = false;
        #endif

        static void Main(string[] args)
        {
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine("DIY Arduino Handheld Game Console Uploading Software\n");

            // Drivers
            Driver driver = new Driver();
            driver.CheckDriver();

            // COM ports
            COMPort comPorts = new COMPort();
            comPorts.printCOMPorts();
            int comPort = comPorts.selectCOMPort();

            // Games
            Games games = new Games();
            games.printGames();
            string game = games.selectGame();

            // Upload
            Uploader uploader = new Uploader();
            uploader.upload(game, comPort);

            Console.ReadLine();
        }
    }
}
