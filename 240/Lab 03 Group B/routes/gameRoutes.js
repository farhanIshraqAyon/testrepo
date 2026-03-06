const express = require('express')
const router = express.Router()

const {
  getGames,
  getGame,
  createGame,
  deleteGame,
  updateGame
} = require('../controllers/gameController')

router.get('/', getGames)

router.get('/:id', getGame)

router.post('/', createGame)

router.delete('/:id', deleteGame)

router.patch('/:id', updateGame)

module.exports = router
