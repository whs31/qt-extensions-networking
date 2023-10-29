//
// Created by whs31 on 29.10.2023.
//

#pragma once

#include <QtNetwork/QUdpSocket>
#include <QtExtensionsNetworking/IConnectable>
#include <QtExtensionsNetworking/NetworkUtils>

namespace QtEx
{
  class UDPSocket : public QUdpSocket,
                    public IConnectable
  {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName FINAL)
    Q_PROPERTY(QString address READ address CONSTANT FINAL)
    Q_PROPERTY(QString ip READ ip CONSTANT FINAL)
    Q_PROPERTY(QString port READ port CONSTANT FINAL)

    public:
      explicit UDPSocket(Qt::Object* parent = nullptr);
      ~UDPSocket() override;

      [[nodiscard]] Qt::String name() const;        void setName(const Qt::String&);
      [[nodiscard]] Qt::String address() const;
      [[nodiscard]] Qt::String ip() const;
      [[nodiscard]] Qt::String port() const;
      [[nodiscard]] QHostAddress addressQHA() const;
      [[nodiscard]] u32 address32() const;
      [[nodiscard]] u16 port16() const;

      invokable void start(const QString& address) noexcept override;
      invokable void stop() noexcept override;

      virtual void send(const Qt::ByteArray& data) noexcept;

    signals:
      void received(QByteArray data);
      void metrics(const QString metric, int size, bool out);

    protected:
      connectable_slot virtual void readSocket() noexcept;

    private:
      Qt::String m_name;
      NetworkUtils::IPV4Address m_address;
  };
} // QtEx

