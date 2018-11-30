this.connect()
this.manager.writeCharacteristicWithResponseForService("00000001-1E3C-FAD4-74E2-97A033F1BFAA", "00000003-1E3C-FAD4-74E2-97A033F1BFAA", btoa("hellllly you"))
    .then((data) =>{
      console.log(data);
      this.setTimeout(()=>{
          this.manager.writeCharacteristicWithResponseForService("00000001-1E3C-FAD4-74E2-97A033F1BFAA", "00000003-1E3C-FAD4-74E2-97A033F1BFAA", btoa("hellllly you"))
              .then((data) =>{
                  console.log(data);
                  this.setTimeout(()=>{
                      this.manager.writeCharacteristicWithResponseForService("00000001-1E3C-FAD4-74E2-97A033F1BFAA", "00000003-1E3C-FAD4-74E2-97A033F1BFAA", btoa("hellllly you"))
                          .then((data) =>{
                              console.log(data);
                              this.setTimeout(()=>{
                                  this.manager.writeCharacteristicWithResponseForService("00000001-1E3C-FAD4-74E2-97A033F1BFAA", "00000003-1E3C-FAD4-74E2-97A033F1BFAA", btoa("hellllly you"))
                                      .then((data) =>{
                                          console.log(data);
                                          this.setTimeout(()=>{
                                              this.manager.writeCharacteristicWithResponseForService("00000001-1E3C-FAD4-74E2-97A033F1BFAA", "00000003-1E3C-FAD4-74E2-97A033F1BFAA", btoa("hellllly you"))
                                                  .then((data) =>{
                                                      console.log(data);
                                                      this.setTimeout(()=>{

                                                      }, 5000)
                                                  }).catch((error4)=>{
                                                  console.log(error4);
                                              })
                                          }, 5000)
                                      }).catch((error3)=>{
                                      console.log(error3);
                                  })
                              }, 5000)
                          }).catch((error2)=>{
                          console.log(error2);
                      })
                  }, 5000)
              }).catch((error1)=>{
              console.log(error1);
          })
      }, 5000)
    })
    .catch((error)=>{
    console.log(error);
    })
