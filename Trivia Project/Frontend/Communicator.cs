using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace Frontend
{
    internal static class Communicator
    {
        private static TcpClient socket;
        private static IPEndPoint endPoint;
        private static NetworkStream stream;

        public enum RequestType
        {
            LoginRequest,
            SignupRequest,
            CreateRoomRequest,
            GetRoomsRequest,
            GetPlayersInRoomRequest,
            JoinRoomRequest,
            GetStatisticsRequest,
            GetLeaderboardRequest,
            LogoutRequest,
            CloseRoomRequest,
            StartGameRequest,
            GetRoomStateRequest,
            LeaveRoomRequest,
            LeaveGameRequest,
            GetQuestionRequest,
            SubmitAnswerRequest,
            GetGameResultRequest,
            AddQuestionRequest
        };


        /// <summary>
        /// Initializing socket, endpoint and stream
        /// </summary>
        /// <param name="ip">server ip</param>
        /// <param name="port">server port</param>
        public static void Init(string ip, int port)
        {
            socket = new TcpClient();
            endPoint = new IPEndPoint(IPAddress.Parse(ip), port);
            socket.Connect(endPoint);

            stream = socket.GetStream();
        }

        /// <summary>
        /// Sending a request to the server
        /// </summary>
        /// <param name="requestHandlerID">request id - type of request</param>
        /// <param name="content">request content</param>
        public static void Send(RequestType requestHandlerID, string content)
        {
            String message = "";
            message += ((int)requestHandlerID).ToString("00"); //adding the id to the message(2 bytes)
            message += content.Length.ToString("0000"); //adding the content size (4 bytes)
            message += content;

            byte[] buffer = new ASCIIEncoding().GetBytes(message);

            stream.Write(buffer, 0, buffer.Length);
            stream.Flush();
        }

        /// <summary>
        /// Receiving a message from server
        /// </summary>
        /// <returns>the message</returns>
        public static String Receive()
        {
            int messageSize;
            byte[] buffer = new byte[4];

            stream.Read(buffer, 0, 4);
            messageSize = int.Parse(Encoding.Default.GetString(buffer));

            buffer = new byte[messageSize];
            stream.Read(buffer, 0, messageSize);

            return Encoding.Default.GetString(buffer);
        }

        public static bool IsDataAvailable()
        {
            return stream.DataAvailable;
        }
    }
}