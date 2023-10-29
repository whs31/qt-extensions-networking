//
// Created by whs31 on 29.10.2023.
//

#include "utils.h"

namespace QtEx::NetworkUtils
{
  auto parseIPv4String(const Qt::String& string) -> expected<IPV4Address, ParseFailure>
  {
    if(not string.contains(":"))
      return unexpected(ParseFailure::NoSemicolon);

    auto spl = string.split(':');
    if(not string.contains("AnyIPv4") and spl.first().split('.').size() != 4)
      return unexpected(ParseFailure::IncorrectAddress);

    QHostAddress ip;
    if(string.contains("AnyIPv4"))
      ip = QHostAddress(QHostAddress::AnyIPv4);
    else
      ip = QHostAddress(spl.first());

    bool uint_success = false;
    uint16_t p = spl.last().toUInt(&uint_success);
    if(not uint_success)
      return unexpected(ParseFailure::IncorrectPort);

    return IPV4Address(ip, p);
  }

  IPV4Address::IPV4Address()
    : address(QHostAddress())
    , port(0)
  {}

  IPV4Address::IPV4Address(const QHostAddress& address, u16 port)
    : address(address)
    , port(port)
  {}

  bool IPV4Address::valid() const
  {
    return not (address.isNull() or port == 0);
  }

  void IPV4Address::clear()
  {
    address.clear();
    port = 0;
  }
} // QtEx::NetworkUtils