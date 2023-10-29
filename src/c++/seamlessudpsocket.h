//
// Created by whs31 on 30.10.2023.
//

#pragma once

#include <QtExtensionsNetworking/UDPSocket>

namespace QtEx
{
  class SeamlessUDPSocket : public UDPSocket
  {
    Q_OBJECT

    public:
      explicit SeamlessUDPSocket(Qt::Object* parent = nullptr);

    protected:
      connectable_slot void readSocket() noexcept override;
  };
} // QtEx
