# wui 라이브러리 개요

wui(Windows UI) 라이브러리는 Windows 기반의 사용자 인터페이스 구성 요소를 관리하고 조작하기 위한 C++ 라이브러리입니다. 이 라이브러리는 윈도우 메시지 처리, 윈도우 생성 및 관리, 사용자 인터페이스 요소의 이벤트 처리 등을 위한 클래스와 함수들을 제공합니다.

## 구성 요소

### Instance 클래스

`Instance` 클래스는 애플리케이션 인스턴스와 관련된 정보와 기능을 제공합니다. 이 클래스는 애플리케이션의 인스턴스 핸들을 관리하고, 리소스 로딩 등의 기능을 수행합니다.

- **파일**: [Instance.hpp](#instance.hpp), [Instance.cpp](#instance.cpp)
- **주요 기능**:
  - 애플리케이션 인스턴스 핸들 관리
  - 리소스 로딩

### Window 클래스

`Window` 클래스는 윈도우를 생성하고 관리하는 기본적인 기능을 제공합니다. 이 클래스는 윈도우 핸들을 관리하고, 윈도우 메시지를 처리하는 메커니즘을 포함합니다.

- **파일**: [Window.hpp](#window.hpp), [Window.cpp](#window.cpp)
- **주요 기능**:
  - 윈도우 핸들 관리
  - 윈도우 메시지 핸들러 등록 및 호출
  - 기본 윈도우 메시지 처리
  
#### Window 자식 클래스

- `SubclassWindow` : common control이나 서브클래싱 윈도우가 필요한 경우 사용합니다.
- `BasicWindow` : frame 윈도우나  view 윈도우에서 사용합니다.
- `BasicModalDialog` : 모달 다이얼로그에서 사용합니다.
- `BasicModelessDialog` 모델리스 다이얼로그에서 사용합니다.

위 클래스들을 이용해서 해당 용도에 맞게 상속받아서 윈도우 클래스를 구현해야 합니다.

### WindowMessage 클래스

`WindowMessage` 클래스는 윈도우 메시지를 나타내는 클래스입니다. 윈도우 프로시저에서 전달되는 메시지 정보를 캡슐화하여 관리합니다.

- **파일**: [WindowMessage.hpp](#windowmessage.hpp), [WindowMessage.cpp](#windowmessage.cpp)
- **주요 기능**:
  - 윈도우 메시지 정보 캡슐화

### WindowMessageLoop 클래스

`WindowMessageLoop` 클래스는 메시지 루프를 실행하여 윈도우 메시지를 처리합니다. 이 클래스는 애플리케이션의 메인 루프에서 사용되어 윈도우 메시지를 지속적으로 수신하고 처리합니다.

- **파일**: [WindowMessageLoop.hpp](#windowmessageloop.hpp), [WindowMessageLoop.cpp](#windowmessageloop.cpp)
- **주요 기능**:
  - 메시지 루프 실행
  - 윈도우 메시지 수신 및 처리

### WindowMessageManipulator 클래스

`WindowMessageManipulator` 클래스는 윈도우 메시지를 조작하기 위한 기능을 제공합니다. 이 클래스는 특정 윈도우 메시지에 대한 데이터 접근 및 조작을 용이하게 합니다.

- **파일**: [WindowMessageManipulator.hpp](#windowmessagemanipulator.hpp), [WindowMessageManipulator.cpp](#windowmessagemanipulator.cpp)
- **주요 기능**:
  - 윈도우 메시지 데이터 접근 및 조작

## 사용 방법

wui 라이브러리를 사용하여 윈도우 기반 애플리케이션을 개발할 때, `Window` 자식 클래스를 상속받아 사용자 정의 윈도우 클래스를 구현합니다. `WindowMessageLoop` 클래스를 사용하여 메시지 루프를 실행하고, `Instance` 클래스를 통해 애플리케이션 인스턴스를 관리합니다. 윈도우 메시지 처리를 위해 `WindowMessage`와 `WindowMessageManipulator` 클래스를 활용할 수 있습니다.

## 결론

wui 라이브러리는 Windows 애플리케이션 개발을 위한 유용한 도구를 제공합니다. 이 라이브러리를 통해 윈도우 생성 및 관리, 메시지 처리, 리소스 관리 등의 작업을 효율적으로 수행할 수 있습니다.