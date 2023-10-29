//
// Created by whs31 on 30.10.2023.
//

#include "seamlessudpsocket.h"
#include <QtNetwork/QNetworkDatagram>

namespace QtEx
{
  SeamlessUDPSocket::SeamlessUDPSocket(Qt::Object* parent)
    : UDPSocket(parent)
  {
    Qt::Object::disconnect(this, &QUdpSocket::readyRead, this, &SeamlessUDPSocket::readSocket);
    Qt::Object::connect(this, &QUdpSocket::readyRead, this, &SeamlessUDPSocket::readSocket, Qt::DirectConnection);
  }

  void SeamlessUDPSocket::readSocket() noexcept
  {
    while(hasPendingDatagrams())
    {
      QNetworkDatagram datagram = this->receiveDatagram();
      emit received(datagram.data());
    }
  }
} // QtEx