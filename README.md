# TeamSHCD : 오목

------

## 왜 '오목'일까요? (Project Planning)

기획은 게임 개발에서 가장 중요합니다.  AAA급 명작 게임에서도, 캐주얼한 국민 게임에서도, 심지어는 콘솔 화면에 출력되는 대학 과제용 C언어 프로젝트 게임에서도요! 저희 SHCD가 만드는 게임이 '오목'인 이유에 대해 설명합니다.

#### 	어떻게 게임을 만들어야 하는가?

`콘솔 환경의 보드게임`이라는 주제에서 많은 의견이 오고갔습니다. 기본적으로 체스형과 카드형로 구분되는 이 장르는 각각 `말` 혹은 `카드`' 를 사용합니다. 둘 모두 훌륭한 방식이지만, `카드`를 사용하는 게임은 제한된 콘솔 환경에서 정보를 표현할 때 많은 부피를 차지한다는 단점이 있습니다.

예를 들어서 흔히 사용하는 포커 카드와 같은 경우 정보를 표현하기위해 최대 3자리(예를 들면, '♥10')를 차지하고, 카드 이미지를 출력하기 위해 카드를 감싸는 Box-drawing 문자(┌, ─, ┐ 등)를 사용할 필요가 있었습니다. 그렇지만 `말`을 이용한 게임은 체스의 우선 Box-drawing문자로 게임판을 그린 뒤, 문자 하나(●, ○ 등)로 표현할 수 있다는 장점이 있습니다. 어떠한 경우에도 게임판 자체는 변하지 않으며, 판 위에 말을 놓는 방식으로 진행됩니다. 콘솔에서 출력하기엔 '카드'보단 '말'이 쉬웠습니다.

#### 	어떤 게임이 더욱 매력적인가?

설령 게임이라 할지라도, 새로운 것을 배우는 것은 언제나 어렵습니다. 더군다나 사운드 출력도 제한되어있고 조작감도 그리 좋지 못하며 칙칙한 콘솔 환경에서라면 그 과정이 지루하기까지 합니다. 따라서 기획 단계에서 고려할 수 있는 사항은 두 가지였습니다.


1. _배우기 쉽도록 간단한 게임_
2. _누구나 알고있어서 배울 필요가 없는 게임_

둘 모두를 만족시키는 게임이라 하면 **오목**이 제격이었습니다. 오목을 모르는 한국인은 굉장히 드물고, 설령 모른다 해도 금방 익힐 수 있습니다.

#### 	인지도와 재미요소, 두 마리 토끼

안타깝게도 '오목'은 그리 신선한 주제가 아닙니다. 그렇지만 주제는 흔해도 부가 요소로 성공한 몇 가지 훌륭한 사례가 있습니다.

- 악당들을 물리치는 슈퍼 히어로를 그린 `아이언맨`
- 매년 몇개씩 나오는 감자칩의 한 종류인 `허니버터칩`
- 그냥 동네 문구점에서 300원에 5개씩 들어있던 `메이플 딱지`

이들은 왜 성공했을까요? 바로 다른 비교군들과 차별화된 요소가 있었기 때문입니다. 주제 자체는 '영웅물, 감자칩, 딱지' 지만, 이들은 차별화된 요소를 가지고 있었습니다.

- 화려한 연출과 탄탄한 세계관이라는 강점을 가진 `아이언맨`
- '감자칩=짠맛'을 깨고 달달하고 고소한 맛으로 나온 `허니버터칩`
- 당시 온라인 게임이던 '메이플스토리'의 몬스터와 그 정보를 써넣었던 `메이플 딱지`

우리는 이 사례들을 보며 '차별 요소가 있는 오목'을 만들기로 했습니다. 높은 인지도와 쉬운 주제는 진부함으로 이어지기 쉽지만, 차별점이 더해진다면 진부함은 대중성으로 바뀔 수 있습니다.

------

## 구동 조건 (Prerequisites)

본 프로젝트와 생성물은 win32 호환 환경에서 이용할 수 있습니다.

------

## 시작하기 (Getting Started)

TeamSHCD-Omok.exe를 실행시키면 별도의 installation 없이 즉시 시작됩니다.

![6](https://user-images.githubusercontent.com/69423873/99976430-c83b7580-2de6-11eb-8e5a-f1f6f10b8773.png)

▲ '오목'과 'N목'을 선택하여 시작할 수 있습니다.

![7](https://user-images.githubusercontent.com/69423873/99976424-c70a4880-2de6-11eb-9286-1c327fde4be2.png)

▲ Player의 이름을 선택하여 시작할 수 있습니다.

![8](https://user-images.githubusercontent.com/69423873/99976428-c83b7580-2de6-11eb-95e9-598973b73da2.png)

▲ 초록색 커서를 이동한 후 `Space`나 `Enter`를 이용하여 착수할 수 있습니다.

------

## 프로젝트에 기여하기 (Contribute)

본 프로젝트는 아래와 같은 cmake 빌드 설정 (CMakeLists.txt)를 사용합니다.

```makefile
cmake_minimum_required(VERSION 3.10)
project(BoardGame C)

set(CMAKE_C_STANDARD 99)

file(GLOB PROJECT_C_FILES "*.c")

file(GLOB PROJECT_HEADER_FILES "inc/*.h")

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(BoardGame ${PROJECT_C_FILES} ${PROJECT_HEADER_FILES})
```

CMakeLists.txt에서 볼 수 있듯 소스 파일은 UTF-8로 저장되어야 하며, C99를 사용합니다.

------

## 라이선스 (License)

![license_badge](https://img.shields.io/badge/license-MIT-green.svg)

------

#### TeamSHCD

[![refracta_link](https://img.shields.io/badge/Collaborator-refracta-blue)](https://github.com/refracta) [![nns503_link](https://img.shields.io/badge/Collaborator-nns503-blue)](https://github.com/nns503) [![korYUSA_link](https://img.shields.io/badge/Collaborator-korYUSA-blue)](https://github.com/korYUSA) 
