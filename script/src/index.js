// Teste: http://localhost:3000/setData?H=23.00&T=25.50

const express = require('express')
const app = express()
const port = 3000

let humidity = 0.0
let temperature = 0.0

app.get('/setData', (req, res) => {
  const { H, T } = req.query

  if (H && T) {
    humidity = parseFloat(H)
    temperature = parseFloat(T)
    console.log('Dados atualizados com sucesso')
  } else {
    res.status(400).send('Parâmetros inválidos')
  }
})

app.get('/getData', (req, res) => {
  const data = {
    humidity,
    temperature
  }
  res.json(data)
})

app.listen(port, () => {
  console.log(`Servidor rodando em http://localhost:${port}`)
})
