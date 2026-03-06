const Player = require('../models/playerModel')

const getPlayers = async (req, res) => {
  const queryObj = {}
  
  if (req.query.membershipLevel) {
    queryObj.membershipLevel = req.query.membershipLevel
  }
  if (req.query.active) {
    queryObj.active = req.query.active
  }

  const players = await Player.find(queryObj).sort({ joinDate: -1 })
  res.status(200).json(players)
}

const getPlayer = async (req, res) => {
  const { id } = req.params

  const player = await Player.findById(id)

  if (!player) {
    return res.status(404).json({ error: 'No such player' })
  }

  res.status(200).json(player)
}

const createPlayer = async (req, res) => {
  const { name, email, age, membershipLevel, active } = req.body

  try {
    const player = await Player.create({ name, email, age, membershipLevel, active })
    res.status(200).json(player)
  } catch (error) {
    res.status(400).json({ error: error.message })
  }
}

// DELETE a player
const deletePlayer = async (req, res) => {
  const { id } = req.params

  const player = await Player.findOneAndDelete({ _id: id })

  if (!player) {
    return res.status(400).json({ error: 'No such player' })
  }

  res.status(200).json(player)
}

const updatePlayer = async (req, res) => {
  const { id } = req.params

  const player = await Player.findOneAndUpdate(
    { _id: id },
    { ...req.body },
    { new: true, runValidators: true } 
  )

  if (!player) {
    return res.status(400).json({ error: 'No such player' })
  }

  res.status(200).json(player)
}

module.exports = {
  getPlayers,
  getPlayer,
  createPlayer,
  deletePlayer,
  updatePlayer
}