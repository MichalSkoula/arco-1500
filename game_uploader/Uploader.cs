using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ARCO1500_Uploader
{
    class Uploader
    {
        public void upload(string game, int comPort)
        {
            string gameTitle = game.Substring(game.LastIndexOf("\\") + 1);

            Console.WriteLine("\nOK! Uploading \"" + gameTitle + "\" to your game console! Please wait.\n");

            // upload game - start arduino ide
            var p = new System.Diagnostics.Process();
            p.StartInfo.FileName = Program.debug ? "..\\..\\..\\..\\arduino\\arduino_debug.exe" : "arduino\\arduino_debug.exe";
            p.StartInfo.Arguments = "--board arduino:avr:uno --port COM" + comPort + " --upload " + game + "\\" + gameTitle + ".ino";
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.CreateNoWindow = false;
            p.Start();
        }
    }
}
