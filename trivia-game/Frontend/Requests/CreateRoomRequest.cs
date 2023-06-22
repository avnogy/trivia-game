namespace Frontend.Requests
{
    internal class CreateRoomRequest
    {
        public string roomName;
        public int maxUsers;
        public int questionCount;
        public int answerTimeout;
    }
}