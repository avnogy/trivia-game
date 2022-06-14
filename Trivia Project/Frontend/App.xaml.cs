using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using Newtonsoft.Json;
using Frontend.Requests;
using Frontend.Responses;

namespace Frontend
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public static string? username;
        private App()
        {
            Communicator.Init("127.0.0.1", 4206);
        }
        public static bool IsInputValidString(string input)
        {
            return input != "" &&
                input != null &&
                input.All(c => char.IsLetterOrDigit(c));
        }
        public static bool IsInputValidInt(string input)
        {
            return input != "" &&
                input != null &&
                input.All(c => char.IsDigit(c));
        }
        public static bool IsInputValidInt(string input, int min, int max)
        {
            return input != "" &&
                input != null &&
                input.All(c => char.IsDigit(c)) &&
                int.Parse(input) >= min &&
                int.Parse(input) <= max;
        }
        private void ExitApp(object sender, ExitEventArgs e)
        {
            Communicator.Send(Communicator.RequestType.LogoutRequest, "");
        }
        

    }
}