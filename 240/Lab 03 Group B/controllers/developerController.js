const Developer = require('../models/developerModel')

const getDevelopers = async (req, res) => {
  const queryObj = {}

  if (req.query.available) {
    queryObj.available = req.query.available
  }


  if (req.query.specialization) {
    queryObj.specializations = req.query.specialization
  }

  const developers = await Developer.find(queryObj).sort({ experienceYears: -1 })
  res.status(200).json(developers)
}


const getDeveloper = async (req, res) => {
  const { id } = req.params

  const developer = await Developer.findById(id)

  if (!developer) {
    return res.status(404).json({ error: 'No such developer' })
  }

  res.status(200).json(developer)
}

const createDeveloper = async (req, res) => {
  const { name, email, specializations, experienceYears, hourlyRate, available, certifications } = req.body

  try {
    const developer = await Developer.create({ 
      name, email, specializations, experienceYears, hourlyRate, available, certifications 
    })
    res.status(200).json(developer)
  } catch (error) {
    res.status(400).json({ error: error.message })
  }
}

const deleteDeveloper = async (req, res) => {
  const { id } = req.params

  const developer = await Developer.findOneAndDelete({ _id: id })

  if (!developer) {
    return res.status(400).json({ error: 'No such developer' })
  }

  res.status(200).json(developer)
}


const updateDeveloper = async (req, res) => {
  const { id } = req.params

  const developer = await Developer.findOneAndUpdate(
    { _id: id },
    { ...req.body },
    { new: true, runValidators: true } 
  )

  if (!developer) {
    return res.status(400).json({ error: 'No such developer' })
  }

  res.status(200).json(developer)
}

module.exports = {
  getDevelopers,
  getDeveloper,
  createDeveloper,
  deleteDeveloper,
  updateDeveloper
}