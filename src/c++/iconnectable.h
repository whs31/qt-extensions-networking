//
// Created by whs31 on 29.10.2023.
//

#pragma once

#include <QtCore/QString>
#include <QtExtensions/QtExtensions>

namespace QtEx
{
  class IConnectable
  {
    public:
      virtual void start(const Qt::String& address) noexcept = 0;
      virtual void stop() noexcept = 0;
  };
} // QtEx
