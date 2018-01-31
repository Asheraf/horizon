//
// Created by SagunKho on 31/01/2018.
//

#include "PacketHandler.hpp"

Horizon::Char::PacketHandler::PacketHandler(std::shared_ptr<CharSession> session)
{
//
}
Horizon::Char::PacketHandler::~PacketHandler()
{

}

template <class T>
void Horizon::Char::PacketHandler::SendPacket(T pkt)
{

}
void Horizon::Char::PacketHandler::SendPacket(PacketBuffer &buf, std::size_t size)
{

}
/**
 *
 */
bool Horizon::Char::PacketHandler::HandleIncomingPacket(PacketBuffer &packet)
{

}