//
// Created by whs31 on 29.10.2023.
//

#include <Libra/Expected>
#include <QtNetwork/QHostAddress>
#include <QtExtensions/QtExtensions>

namespace QtEx::NetworkUtils
{
  enum class ParseFailure
  {
    NoSemicolon,
    IncorrectPort,
    IncorrectAddress
  };

  enum class ChecksumMode
  {
    CRC16,
    CRC16CCIITT
  };

  struct IPV4Address
  {
    IPV4Address();
    IPV4Address(const QHostAddress& address, u16 port);

    [[nodiscard]] bool valid() const;

    void clear();

    QHostAddress address;
    u16 port;
  };

  auto parseIPv4String(const Qt::String& string) -> expected<IPV4Address, ParseFailure>;
  auto checksum(const char* data, int size, ChecksumMode) noexcept -> u16;
  auto stringToChar(const QString& str) noexcept -> char*;
} // QtEx::NetworkUtils

