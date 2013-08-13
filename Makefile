all:
	node-gyp clean
	node-gyp configure
	node-gyp build

clean:
	node-gyp clean

