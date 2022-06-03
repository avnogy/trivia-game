using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace Frontend
{
    internal class Communicator
    {
        private TcpClient socket;
        private IPEndPoint endPoint;
        private NetworkStream stream;

        public enum RequestHandlerID
        {
            LoginRequest,
            SignupRequest,
            CreateRoomRequest,
            GetRoomsRequest,
            GetPlayersInRoomRequest,
            JoinRoomRequest,
            GetStatisticsRequest,
            LogoutRequest,
            CloseRoomRequest,
            StartGameRequest,
            GetRoomStateRequest,
            LeaveRoomRequest
        };

        public Communicator(String ip, int port)
        {
            this.socket = new TcpClient();
            this.endPoint = new IPEndPoint(IPAddress.Parse(ip), port);
            socket.Connect(endPoint);

            this.stream = socket.GetStream();
        }

        public void Send(RequestHandlerID requestHandlerID, string content)
        {
            String message = "";
            message += requestHandlerID.ToString("00"); //adding the id to the message(2 bytes)
            message += content.Length.ToString("0000"); //adding the content size (4 bytes)
            message += content;

            byte[] buffer = new ASCIIEncoding().GetBytes(message);

            this.stream.Write(buffer, 0, buffer.Length);
        }
    }
}