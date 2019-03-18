set -x
pushd .
brew install wget gnupg unzip

if ! test -f "/usr/local/include/sol.hpp"; then
	pushd /tmp;
	echo "Sol2 doesn't exist, installing from scratch!";
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

brew install readline luajit zlib spdlog boost cryptopp mysql openssl

if ! test -f "/usr/local/mysql-connector-c++/mysqlx/xdevapi.h"; then
	pushd /tmp;
	cppconn_filename="mysql-connector-c++-8.0.15-macos10.14-x86-64bit"
	wget https://dev.mysql.com/get/Downloads/Connector-C++/${cppconn_filename}.tar.gz;
	tar -xvf ${cppconn_filename}.tar.gz;
	sudo cp ${cppconn_filename}/lib64/libssl.1.0.0.dylib /usr/local/lib/libssl.1.0.0.dylib
	sudo cp ${cppconn_filename}/lib64/libcrypto.1.0.0.dylib /usr/local/lib/libcrypto.1.0.0.dylib
	sudo mv ${cppconn_filename} /usr/local/mysql-connector-c++;
	popd;
fi

popd;
