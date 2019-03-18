function vercomp () {
    if [[ $1 == $2 ]]
    then
        return 0
    fi
    local IFS=.
    local i ver1=($1) ver2=($2)
    # fill empty fields in ver1 with zeros
    for ((i=${#ver1[@]}; i<${#ver2[@]}; i++))
    do
        ver1[i]=0
    done
    for ((i=0; i<${#ver1[@]}; i++))
    do
        if [[ -z ${ver2[i]} ]]
        then
            # fill empty fields in ver2 with zeros
            ver2[i]=0
        fi
        if ((10#${ver1[i]} > 10#${ver2[i]}))
        then
            return 1
        fi
        if ((10#${ver1[i]} < 10#${ver2[i]}))
        then
            return 2
        fi
    done
    return 0
}

set -x

# Cmake version upgrade. (Not Required currently, also incomplete)
# cmake_version="$(cmake --version | grep -o -E "([0-9]+).([0-9]+).([0-9]+)")"
# req_cmake_version="3.13.2"
# vercomp "$cmake_version" "$req_cmake_version"
# if [ $? -eq 2 ]; then
# 	rm -rf /usr/bin/cmake;
# 	export PATH="$PATH:/usr/local/bin"
# 	echo "CMake version '$cmake_version' does not satisfy '$req_cmake_version', installing latest...";
# 	wget https://github.com/Kitware/CMake/releases/download/v3.13.4/cmake-3.13.4.tar.gz;
# 	tar -xvf cmake-3.13.4.tar.gz >/dev/null;
# 	cd cmake-3.13.4;
# 	echo "Silently building and installing CMake...";
# 	./bootstrap >/dev/null;
# else
# 	echo "CMake version $cmake_version is installed and compatible.";
# fi

pushd .

sudo apt-get -y update;
sudo apt-get -y install wget lsb-release gnupg unzip;

if ! test -f "/usr/local/include/sol.hpp"; then
	echo "Sol2 doesn't exist, installing from scratch!";
	pushd /tmp;
	git clone https://github.com/ThePhD/sol2.git;
	mkdir sol2/build;
	pushd sol2/build;
	cmake ../;
	echo "Silently building and installing Sol2...";
	sudo make install >/dev/null;
	popd;
	popd;
else
	echo "Sol2 already exists, skipping installation...";
fi

wget https://launchpad.net/ubuntu/+archive/primary/+files/libspdlog-dev_1.3.1-1_amd64.deb;
sudo dpkg -i libspdlog-dev_1.3.1-1_amd64.deb;
sudo apt-get -y install libreadline-dev libluajit-5.1-dev zlib1g-dev;

if ! test -f "/usr/local/include/boost/version.hpp"; then
	echo "Boost doesn't exist, installing from scratch!";
	pushd /tmp;
	wget https://dl.bintray.com/boostorg/release/1.69.0/source/boost_1_69_0.tar.gz;
	tar -xvf boost_1_69_0.tar.gz >/dev/null;
	pushd boost_1_69_0;
	echo "Silently building and installing Boost Filesystem, System, Thread, Locale and Test libraries...";
	./bootstrap.sh --with-toolset=${TOOLSET} >/dev/null;
	sudo ./b2 install threading=multi toolset=${TOOLSET} --with-system  --with-filesystem --with-thread --with-locale --with-test -d0;
	popd;
	popd;
else
	echo "Boost already exists, skipping installation...";
fi

if ! test -f "/usr/local/include/cryptopp/scrypt.h"; then
	echo "Crypto++ with Scrypt wasn't found, installing v8.1 from scratch!";
	pushd /tmp;
	wget https://www.cryptopp.com/cryptopp810.zip;
	echo "Silently building and installing Crypto++...";
	sudo unzip cryptopp810.zip -d cryptopp >/dev/null;
	pushd cryptopp;
	sudo make >/dev/null;
	sudo make install PREFIX=/usr/local;
	popd;
	popd;
else
	echo "Crypto++ already exists, skipping installation..."
fi

mysql_version="$(mysql --version | grep -o -E "([0-9]+).([0-9]+).([0-9]+)")"
req_mysql_version="8.0.15"
vercomp "$mysql_version" "$req_mysql_version"

if [ $? -eq 2 ]; then
	echo "MySQL 8.0.15 is required but not found, installing latest..."
	pushd /tmp;
	wget https://dev.mysql.com/get/mysql-apt-config_0.8.12-1_all.deb;
	sudo dpkg -i mysql-apt-config_0.8.12-1_all.deb;
	popd;
	sudo apt-get -y update;
	sudo apt-get -y install mysql-server mysql-client libmysqlcppconn-dev;
else
	echo "MySQL 8.0.15 is already installed."
fi

popd;
