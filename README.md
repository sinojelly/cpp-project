= 背景介绍 =

    cpp-project是使用testngpp、mockcpp、cpp-ut-project的一个具体实例，是为了方便使用者使用，达到解压缩即可编译运行的目的而创建的项目。由于testngpp、mockcpp的库文件与平台紧密相关，我这里无法把所有平台的库文件都生成一遍，所以也放入了编译它们的源代码文件。

    此项目假定工具是放在项目目录下的，这样便于获取项目代码即可开始测试。当然也可以把testngpp、mockcpp安装到电脑的某个安装目录，供本机的所有项目使用，Linux上一般是直接安装到usr/local目录下。

= 使用方法 =

== 编译运行平台是cpp-project已经支持的 ==

    按照如下步骤使用即可：

    # 下载cpp-project最新的压缩包。（地址：http://code.google.com/p/cpp-project/downloads/list）
    # 解压缩cpp-project压缩包。
    # 【Linux】命令行进入cpp-project\src\module1，执行premake4 gmake，然后进入cpp-project\build\module1\gmake，执行make。
    # 【Windows】打开cpp-project\build\module1\vs200x\module1.sln，编译运行。（另外，也可类似Linux一样通过premake4 vs2008重新生成工程）

    注意：
    * 构建中需要用到的工具在cpp-project\tools\bin目录下。
    * 当前支持：Win32 vs2008, Linux32. （其它更高版本的vs也许支持，未验证）
    * VS下，只编译了MDd版本，如果需要MTd的，请参考下面一节自己编译，需要修改工程设置。
    * Linux下需要设置可执行文件属性为可执行。参考下面命令可以运行样例工程：
        * sudo cp tools/bin/premake4 /usr/bin
        * sudo chmod 755 /usr/bin/premake4
        * sudo chmod 755 tools/testngpp/bin/testngppgen
        * sudo chmod 755 tools/testngpp/bin/testngpp-runner
        * cd src/module1
        * premake4 gmake
        * cd ../../build/module1/gmake
        * make

== 编译运行平台是cpp-project未支持的 ==

    先按照如下步骤生成自己平台需要的库文件：

    # 在cpp-project\tools_src\mockcpp\mockcpp目录下执行build_install.ps1。（可修改安装路径到任意自己指定的位置）
    # 在cpp-project\tools_src\testngpp目录下执行build_install.ps1。（可修改安装路径到任意自己指定的位置）
    # 把上述两步生成的如下文件拷贝到cpp-project\tools目录下的对应子目录中，并且加上自己的平台后缀如-vs2005，全小写，没有空格。（只要VS版本相同，库和可执行文件一般是通用的，Windows版本不同，不影响使用。如果某些时候，需要区分OS类型，也可以用-ostype-compilertype的方式。如果是其它平台，也是类似处理，不过不需要修改文件名加类似-vs2005的后缀。）
      * mockcpp.lib  (路径：mockcpp/lib/mockcpp.lib)
      * testngpp-runner.exe (路径：testngpp/bin/testngpp-runner.exe)
      * testngpp-win32-testcase-runner.exe (路径：testngpp/bin/testngpp-win32-testcase-runner.exe)
      * testngpp.lib (路径：testngpp/lib/testngpp.lib)
      * testngppstdoutlistener.dll (路径：testngpp/testngpp/listener/testngppstdoutlistener.dll)
      * testngppxmllistener.dll (路径：testngpp/testngpp/listener/testngppxmllistener.dll)

    注意：编译中需要用到boost，可从cpp-project\tools\3rdparty\boost拷贝。

    然后按照前面一节讲述的编译运行方法使用即可。

== 应用到自己项目的方法 ==

    cpp-project代码组织方式是按模块来的，每个模块对应一个源代码目录、一个头文件目录 和 一个测试代码目录。在模块的源代码目录中，还有一个工程自动生成的脚本文件premake4.lua，通过它可以自动生成任意指定平台的工程，比如VS2008工程，或者GNU Make的Makefile文件。生成测试工程是用的它，生成编译产品的工程也可以用它。

    所以，应用到产品的时候，建议也用目录来体现模块，给每个模块提供一个premake4.lua，通过简单配置，可以指定该模块的源文件、头文件位置，以及依赖的别的库等等。

    编译运行之前，在premake4.lua所在目录执行premake4 vs2008这样的命令，即可在指定的build目录中生成工程。

== 升级相关工具的办法 ==

    * 升级mockcpp、testngpp的方法：从对应的开源项目中取最新代码，替换tools_src中的对应目录，然后重新编译它们的库、可执行文件等，并覆盖tools下的对应目录。
    * 升级premake的方法：从premake开源项目下载，或者获取它的源代码自己编译。
    * 升级cpp-ut-project的方法：从它的开源项目获取最新代码，把差异合入cpp-project\tools\scripts。（如果模块对应的premake4.lua有变化也要合入）

    这些工具的开源项目网址如下：
    * testngpp    http://code.google.com/p/test-ng-pp/
    * mockcpp   http://code.google.com/p/mockcpp/
    * premake     http://industriousone.com/premake
    * cpp-ut-project http://code.google.com/p/cpp-ut-project/

= 使用此项目进行TDD的方法 =

    首先，需要遵循的原则是针对模块进行TDD，一般业界也是按照这个标准。当然，这里的模块指的是一个目录，它里面可能有多个更小的模块或者类。

    TDD的步骤如下：
    # 设计一个类，并且初步考虑它的对外接口。
    # 用premake4 --class=!MyClass --test addfile生成对应的文件。（直接在资源管理器创建文件也可以，但毕竟麻烦）
    # 用premake4 vs2008重新生成工程。
    # 编译、运行，会发现有用例不过，提示在该位置写上自己的用例。
    # 根据提示，写上自己的用例。编译、运行，用例不过。
    # 在对应的模块写上实现，使得上述用例通过。
    # 重构 ......

    一个功能涉及的模块/类都开发完成后，再做集成测试，可以用premake4 --feature=!FeatureName addfile来生成集成测试文件。

    可以用premake4 --usage addfile了解更多自动添加文件的命令。

= FAQ =

    * testngpp-runner.exe 无法运行，或者listener dll文件无法加载。
    * 答：这可能是编译testngpp的vs环境与使用者不一致导致的。可以参考tools\vsruntime下的说明，把编译者环境上的几个vs相关文件拷贝到可执行文件目录和dll目录即可，也可以拷贝到系统目录，或者把vsruntime\vs200x路径添加到环境变量。
