using System.Collections.Generic;

namespace Frontend.Responses
{
    internal struct GetRoomsResponse
    {
        public int status;
        public List<RoomData> rooms;
    }
}