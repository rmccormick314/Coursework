const express = require('express')
const logger = require('morgan')
const path = require('path')
const server = express()
server.use(express.urlencoded({'extended': true}))
server.use(logger('dev'))

// Routes
server.get('/do_a_random', (req, res) => {
  res.send(`Your number is: ${Math.floor(Math.random() * 100) + 1}`)
})

server.post('/cs212/homework/8/', (req, res) => {
	response_string = (req.body.fname
			+ " was walking to the store to buy some "
			+ req.body.fav_food
			+ ", their favorite food."
			+ " All of a sudden, a "
			+ req.body.color + " " + req.body.animal
			+ " jumped out at them from behind the bushes!"
			+ " Someone had tried to poison it by feeding the "
			+ req.body.animal
			+ " some disgusting " + req.body.worst_food + "! "
			+ req.body.fname + " hugged the "
			+ req.body.color + " " + req.body.animal
			+ ", and took it to get some delicious "
			+ req.body.fav_food + " and help it feel better.")

	res.send(response_string)
})


// Setup static page serving for all the pages in "public"
const publicServedFilesPath = path.join(__dirname, 'public')
server.use(express.static(publicServedFilesPath))


// The server uses port 80 by default unless you start it with the extra
// command line argument 'local' like this:
//       node server.js local
let port = 80
if (process.argv[2] === 'local') {
  port = 8080
}

server.listen(port, () => console.log('Ready on localhost!'))
