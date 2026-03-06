// developerModel.js
const mongoose = require('mongoose');

const developerSchema = new mongoose.Schema({
  name: {
    type: String,
    required: true
  },
  email: {
    type: String,
    required: true,
    unique: true,
    trim: true,
    lowercase: true
  },
  specializations: {
    type: [String],
    enum: ['RPG', 'FPS', 'Puzzle', 'Strategy', 'Simulation']
  },
  experienceYears: {
    type: Number,
    min: 1
  },
  hourlyRate: {
    type: Number,
    required: true,
    min: 10
  },
  available: {
    type: Boolean,
    default: true
  },
  certifications: {
    type: [String]
  }
});

module.exports = mongoose.model('Developer', developerSchema);