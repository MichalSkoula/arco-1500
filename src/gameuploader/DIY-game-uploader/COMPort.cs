using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace DIY_game_uploader
{
    class COMPort
    {
        private int comPort;
        private List<int> availablePortNumbers;

        public void printCOMPorts()
        {
            Console.WriteLine("Available COM ports:");
            availablePortNumbers = new List<int>();
            foreach (string s in System.IO.Ports.SerialPort.GetPortNames())
            {
                Console.WriteLine(s.Substring(3) + ": " + s);
                availablePortNumbers.Add(int.Parse(s.Substring(3)));
            }
        }

        public int selectCOMPort()
        {
            do
            {
                Console.WriteLine("\nInsert your console's COM port number and press ENTER");
                string comPortRead = Console.ReadLine();
                if (!Regex.IsMatch(comPortRead, @"^\d+$"))
                {
                    comPort = -1;
                }
                else
                {
                    comPort = int.Parse(comPortRead);
                }
            } while (availablePortNumbers.IndexOf(comPort) == -1);

            return comPort;
        }

        public int getCOMPort()
        {
            return comPort;
        }
    }
}
