namespace Frontend.Responses
{
    internal struct UpdateResponse
    {
        public enum Type
        {
            StartGame,
            LeaveRoom
        };

        public int status;
        public int type;
    }
}