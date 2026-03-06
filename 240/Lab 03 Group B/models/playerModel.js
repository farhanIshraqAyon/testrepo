const mongoose = require('mongoose');

const playerSchema = new mongoose.Schema({
  name: {
    type: String,
    required: [true]
  },
  email: {
    type: String,
    required: [true],
    unique: true, 
    trim: true,
    lowercase: true
  },
  age: {
    type: Number,
    min: [12],
    max: [100]
  },
  membershipLevel: {
    type: String,
    enum: {
      values: ['free', 'premium', 'elite'],
    },
    default: 'free'
  },
  joinDate: {
    type: Date,
    default: Date.now 
  },
  active: {
    type: Boolean,
    default: true
  }
});

// Create and export the model
const Player = mongoose.model('Player', playerSchema);

module.exports = Player;