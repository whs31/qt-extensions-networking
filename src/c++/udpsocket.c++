//
// Created by whs31 on 29.10.2023.
//

#include "udpsocket.h"
#include <QtExtensions/Logging>

namespace QtEx
{
  UDPSocket::UDPSocket(Qt::Object* parent)
    : QUdpSocket(parent)
    , m_name("Unnamed socket")
    , m_address({QHostAddress::LocalHost, 25565})
  {
    Qt::Object::connect(this, &QUdpSocket::readyRead, this, &UDPSocket::readSocket, Qt::DirectConnection);
  }

  UDPSocket::~UDPSocket() { this->stop(); }

  Qt::String UDPSocket::name() const { return m_name; }
  void UDPSocket::setName(const Qt::String& x) { m_name = x; }
  Qt::String UDPSocket::address() const { return String("%1:%2").arg(ip(), port()); }
  Qt::String UDPSocket::ip() const { return addressQHA().toString(); }
  Qt::String UDPSocket::port() const { return String::number(port16()); }
  QHostAddress UDPSocket::addressQHA() const { return m_address.address; }
  u32 UDPSocket::address32() const { return addressQHA().toIPv4Address(); }
  u16 UDPSocket::port16() const { return m_address.port; }

  void UDPSocket::start(const QString& addr) noexcept
  {
    auto parse = NetworkUtils::parseIPv4String(addr);
    if(not parse.has_value())
    {
      llog(Error) "Incorrect address provided:" << addr;
      return;
    }

    llog(Info) "Starting UDP socket named" << name() << "on" << addr;
    m_address = parse.value();
    this->bind(addressQHA(), port16());
    emit metrics("Socket opened on " + address(), 0, true);
  }

  void UDPSocket::stop() noexcept
  {
    llog(Info) "Closing UDP socket named" << name();
    this->close();
    m_address.clear();
    emit metrics("Socket closed", 0, true);
  }

  void UDPSocket::send(const Qt::ByteArray& data) noexcept
  {
    if(not m_address.valid())
      llog(Warning) "UDP socket named" << name() << "is trying to write to null host";
    this->writeDatagram(data, addressQHA(), port16());
  }

  void UDPSocket::readSocket() noexcept
  {
    QByteArray buffer(static_cast<isize>(pendingDatagramSize()), 0x0);
    while(hasPendingDatagrams())
      this->readDatagram(buffer.data(), buffer.size(), &m_address.address, &m_address.port);
    emit received(buffer);
  }
} // QtEx